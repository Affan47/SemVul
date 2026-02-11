getPixel(double x,double y ) const
{

	const size_t W = m_img->getWidth();
	const size_t H = m_img->getHeight();


	const double px = (x-m_x0)/m_pixel_size;
	const double py = (y-m_y0)/m_pixel_size;

	if (px<0 || py<0 || px>W || py>H) { return 0; }

	switch (m_method)
	{
	case IMG_INTERP_NN:
		{

			const int px0 = mrpt::utils::round(px);
			const int py0 = mrpt::utils::round(py);
			return static_cast<double>(*m_img->get_unsafe(px0, py0));
		}
		break;
	case IMG_INTERP_LINEAR:
		{


			const int px0 = (int)floor(px);
			const int px1 = (int)ceil(px);
			const int py0 = (int)floor(py);
			const int py1 = (int)ceil(py);

			const double P11 = static_cast<double>(*m_img->get_unsafe(px0, py0));
			const double P12 = static_cast<double>(*m_img->get_unsafe(px0, py1));
			const double P21 = static_cast<double>(*m_img->get_unsafe(px1, py0));
			const double P22 = static_cast<double>(*m_img->get_unsafe(px1, py1));

			const double R1 = P11*(px1-px)  + P21*(px-px0) ;
			const double R2 = P12*(px1-px)  + P22*(px-px0) ;

			return R1 * (py1-py) + R2 * (py-py0);
		}
		break;

	case IMG_INTERP_CUBIC:
		{
			THROW_EXCEPTION("TO DO!");
		}
		break;

	case IMG_INTERP_AREA:
	default:
		THROW_EXCEPTION("The selected interpolation method is not supported in this method.");
	};

}
