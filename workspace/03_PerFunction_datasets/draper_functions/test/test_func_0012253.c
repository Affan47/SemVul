gf_sc_svg_convert_length_to_display(GF_Compositor *compositor, SVG_Length *length)
{

	u32 dpi = 90;
	if (!length) return 0;

	switch (length->type) {
	case SVG_NUMBER_PERCENTAGE:
		break;
	case SVG_NUMBER_EMS:
		break;
	case SVG_NUMBER_EXS:
		break;
	case SVG_NUMBER_VALUE:
		break;
	case SVG_NUMBER_PX:
		return length->value;
	case SVG_NUMBER_CM:
		return gf_mulfix(length->value, dpi*FLT2FIX(0.39));
		break;
	case SVG_NUMBER_MM:
		return gf_mulfix(length->value, dpi*FLT2FIX(0.039));
	case SVG_NUMBER_IN:
		return length->value * dpi;
	case SVG_NUMBER_PT:
		return (dpi * length->value) / 12;
	case SVG_NUMBER_PC:
		return (dpi*length->value) / 6;
	case SVG_NUMBER_INHERIT:
		break;
	}
	return length->value;
}
