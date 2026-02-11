GMT_fancy_frame_extension (double angle, double extend[2])
{


	double s, c;
	sincosd (angle, &s, &c);
	extend[0] = (gmtdefs.basemap_type == GMT_IS_ROUNDED) ? 0.0 : gmtdefs.frame_width * c;
	extend[1] = (gmtdefs.basemap_type == GMT_IS_ROUNDED) ? 0.0 : gmtdefs.frame_width * s;
}
