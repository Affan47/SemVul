jacobian_project_with_distortion(const mrpt::math::TPoint3D &p3D, math::CMatrixDouble & dh_dy ) const
{


	ASSERT_(p3D.z!=0)

	CMatrixDouble  du_dy(2,3);

	du_dy(0,0) = cam.fx() / p3D.z;  du_dy(0,2) = - p3D.x * cam.fx() / square(p3D.z);
	du_dy(1,1) = cam.fy() / p3D.z;  du_dy(1,2) = - p3D.y * cam.fy() / square(p3D.z);


	const double ux = (p3D.x / p3D.z)*cam.fx();
	const double uy = (p3D.y / p3D.z)*cam.fy();

	const double ux_sqr = square(ux);
	const double uy_sqr = square(uy);

	const double r2 = ux_sqr + uy_sqr;

	const double f = 1+2*cam.k1()*r2;
    const double f1_2 = sqrt(f);
    const double f3_2 = f1_2 * f;


	CMatrixDouble  dh_du(2,2);
	dh_du *= -2 * cam.k1() / f3_2;
	dh_du(0,0) += (1/f1_2);
	dh_du(1,1) += (1/f1_2);


	dh_dy.multiply( dh_du, du_dy );
}
