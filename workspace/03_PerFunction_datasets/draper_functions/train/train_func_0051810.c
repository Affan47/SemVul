solo_fillbuf(struct solo_dev *solo_dev,
			 struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	dma_addr_t addr;
	unsigned int fdma_addr;
	int error = -1;
	int i;

	addr = vb2_dma_contig_plane_dma_addr(vb, 0);
	if (!addr)
		goto finish_buf;

	if (erase_off(solo_dev)) {
		void *p = vb2_plane_vaddr(vb, 0);
		int image_size = solo_image_size(solo_dev);

		for (i = 0; i < image_size; i += 2) {
			((u8 *)p)[i] = 0x80;
			((u8 *)p)[i + 1] = 0x00;
		}
		error = 0;
	} else {
		fdma_addr = SOLO_DISP_EXT_ADDR + (solo_dev->old_write *
				(SOLO_HW_BPL * solo_vlines(solo_dev)));

		error = solo_p2m_dma_t(solo_dev, 0, addr, fdma_addr,
				       solo_bytesperline(solo_dev),
				       solo_vlines(solo_dev), SOLO_HW_BPL);
	}

finish_buf:
	if (!error) {
		vb2_set_plane_payload(vb, 0,
			solo_vlines(solo_dev) * solo_bytesperline(solo_dev));
		vbuf->sequence = solo_dev->sequence++;
		v4l2_get_timestamp(&vbuf->timestamp);
	}

	vb2_buffer_done(vb, error ? VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
}
