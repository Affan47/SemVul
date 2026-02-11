project_3D_point(const mrpt::math::TPoint3D &p3D, mrpt::utils::TPixelCoordf &distorted_p) const
{


	ASSERT_(p3D.z!=0)
	const double dx = (p3D.x / p3D.z)*cam.fx();
	const double dy = (p3D.y / p3D.z)*cam.fy();


	const double r2 = square(dx) + square(dy);

	const double fact = 1.0/sqrt(1+2*cam.k1()*r2);

	distorted_p.x = cam.cx() + dx*fact;
	distorted_p.y = cam.cy() + dy*fact;
}
