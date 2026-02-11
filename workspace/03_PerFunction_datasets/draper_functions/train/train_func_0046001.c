weibull_critval (double shape, double scale, double rtail)
{
    double ret = NADBL;

    if (shape > 0 && scale > 0 && rtail > 0 && rtail < 1) {
	ret = scale * pow(-log(rtail), 1.0 / shape);
    }

    return ret;
}
