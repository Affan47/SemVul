quantize_duodecimal_tics(double arg, int guide)
{

    double power = pow(12.0, floor(log(arg)/log(12.0)));
    double xnorm = arg / power;
    double posns = guide / xnorm;

    if (posns > 24)
	return power / 24;
    else if (posns > 12)
	return power / 12;
    else if (posns > 6)
	return power / 6;
    else if (posns > 4)
	return power / 4;
    else if (posns > 2)
	return power / 2;
    else if (posns > 1)
	return power;
    else if (posns > 0.5)
	return power * 2;
    else if (posns > 1.0/3)
	return power * 3;
    else


	return power * ceil(xnorm);
}
