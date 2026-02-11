radeon_align_pitch(struct radeon_device *rdev, int width, int bpp, bool tiled)
{
	int aligned = width;
	int align_large = (ASIC_IS_AVIVO(rdev)) || tiled;
	int pitch_mask = 0;

	switch (bpp / 8) {
	case 1:
		pitch_mask = align_large ? 255 : 127;
		break;
	case 2:
		pitch_mask = align_large ? 127 : 31;
		break;
	case 3:
	case 4:
		pitch_mask = align_large ? 63 : 15;
		break;
	}

	aligned += pitch_mask;
	aligned &= ~pitch_mask;
	return aligned;
}
