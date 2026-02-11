SaveCurve(floatish *y, floatish *py)
{
    intish i;

    for (i = 0; i < nsamples; i++) {
	py[i] = y[i];
    }
}
