getPathPose(uint16_t k, uint16_t step, mrpt::math::TPose2D &p) const
{
	const double t = PATH_TIME_STEP*step;
	const double dir = CParameterizedTrajectoryGenerator::index2alpha(k);

	const double TR2_ = 1.0/(2*T_ramp);
	const double vxf = V_MAX * cos(dir), vyf = V_MAX * sin(dir);
	const double vxi = curVelLocal.vx, vyi = curVelLocal.vy;


	if (t<T_ramp)
	{
		p.x   = vxi * t + t*t * TR2_ * (vxf-vxi);
		p.y   = vyi * t + t*t * TR2_ * (vyf-vyi);
	}
	else
	{
		p.x   = T_ramp *0.5*(vxi+vxf) + (t-T_ramp) * vxf;
		p.y   = T_ramp *0.5*(vyi+vyf) + (t-T_ramp) * vyf;
	}


	const double T_rot = std::abs(dir)/W_MAX;
	if (t<T_rot)
	     p.phi = t*dir/T_rot;
	else p.phi = dir;
}
