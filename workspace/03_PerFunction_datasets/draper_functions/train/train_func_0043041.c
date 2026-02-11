calc_trans_distance_t_below_Tramp(double k2, double k4, double vxi,double vyi, double t)
{


	const double c = (vxi*vxi+vyi*vyi);
	if (std::abs(k2)>eps || std::abs(k4)>eps)
	{
		const double a = ((k2*k2)*4.0+(k4*k4)*4.0);
		const double b = (k2*vxi*4.0+k4*vyi*4.0);


		if (std::abs(b)<eps && std::abs(c)<eps) {

			const double int_t = sqrt(a)*(t*t)*0.5;
			return int_t;
		}
		else {
			return calc_trans_distance_t_below_Tramp_abc(t,a,b,c);
		}
	}
	else {
		return std::sqrt(c)*t;
	}
}
