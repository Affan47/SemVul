r300_emit_3d_load_vbpntr(drm_radeon_private_t *dev_priv,
					       drm_radeon_kcmd_buffer_t *cmdbuf,
					       u32 header)
{
	int count, i, k;
#define MAX_ARRAY_PACKET  64
	u32 *data;
	u32 narrays;
	RING_LOCALS;

	count = (header & RADEON_CP_PACKET_COUNT_MASK) >> 16;

	if ((count + 1) > MAX_ARRAY_PACKET) {
		DRM_ERROR("Too large payload in 3D_LOAD_VBPNTR (count=%d)\n",
			  count);
		return -EINVAL;
	}


	drm_buffer_advance(cmdbuf->buffer, 4);

	narrays = *(u32 *)drm_buffer_pointer_to_dword(cmdbuf->buffer, 0);
	k = 0;
	i = 1;
	while ((k < narrays) && (i < (count + 1))) {
		i++;
		data = drm_buffer_pointer_to_dword(cmdbuf->buffer, i);
		if (!radeon_check_offset(dev_priv, *data)) {
			DRM_ERROR
			    ("Offset failed range check (k=%d i=%d) while processing 3D_LOAD_VBPNTR packet.\n",
			     k, i);
			return -EINVAL;
		}
		k++;
		i++;
		if (k == narrays)
			break;

		data = drm_buffer_pointer_to_dword(cmdbuf->buffer, i);
		if (!radeon_check_offset(dev_priv, *data)) {
			DRM_ERROR
			    ("Offset failed range check (k=%d i=%d) while processing 3D_LOAD_VBPNTR packet.\n",
			     k, i);
			return -EINVAL;
		}
		k++;
		i++;
	}

	if ((k != narrays) || (i != (count + 1))) {
		DRM_ERROR
		    ("Malformed 3D_LOAD_VBPNTR packet (k=%d i=%d narrays=%d count+1=%d).\n",
		     k, i, narrays, count + 1);
		return -EINVAL;
	}


	BEGIN_RING(count + 2);
	OUT_RING(header);
	OUT_RING_DRM_BUFFER(cmdbuf->buffer, count + 1);
	ADVANCE_RING();

	return 0;
}
