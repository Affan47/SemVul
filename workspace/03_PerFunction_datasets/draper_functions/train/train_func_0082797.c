act_nominal_width_delta(int cmd, double delta)
{
    double d = (_program ? _program->global_width_x(true) : UNKDOUBLE);
    if (KNOWN(d))
	act_width(cmd, Point(d + delta, 0));
}
