mx2_videobuf_prepare(struct vb2_buffer *vb)
{
	struct soc_camera_device *icd = soc_camera_from_vb2q(vb->vb2_queue);
	int ret = 0;

	dev_dbg(icd->parent, "%s (vb=0x%p) 0x%p %lu\n", __func__,
		vb, vb2_plane_vaddr(vb, 0), vb2_get_plane_payload(vb, 0));

#ifdef DEBUG


	memset((void *)vb2_plane_vaddr(vb, 0),
	       0xaa, vb2_get_plane_payload(vb, 0));
#endif

	vb2_set_plane_payload(vb, 0, icd->sizeimage);
	if (vb2_plane_vaddr(vb, 0) &&
	    vb2_get_plane_payload(vb, 0) > vb2_plane_size(vb, 0)) {
		ret = -EINVAL;
		goto out;
	}

	return 0;

out:
	return ret;
}
