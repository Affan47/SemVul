radeon_uvd_validate_codec(struct radeon_cs_parser *p,
				     unsigned stream_type)
{
	switch (stream_type) {
	case 0:
	case 1:

		return 0;

	case 3:
	case 4:

		if (p->rdev->family >= CHIP_PALM)
			return 0;


	default:
		DRM_ERROR("UVD codec not supported by hardware %d!\n",
			  stream_type);
		return -EINVAL;
	}
}
