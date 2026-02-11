make_red_yellow_ramp(int *ramp, int num, int minval, int maxval)
{
    int g, i, incr;

    incr = (maxval - minval) / (num - 1);
    for (i = 0; i < num; i++) {
	g = minval + incr * i;
	RGB_TO_INT(maxval, g, 0, ramp[i]);
    }

    return 0;
}
