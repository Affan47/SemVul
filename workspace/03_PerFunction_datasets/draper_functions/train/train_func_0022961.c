endAngleRadConstrained()
{


	double e = endAngleRad();
	double s = startAngleRad();
	while (e < s)
		e += 2*M_PI;
	return(e);
}
