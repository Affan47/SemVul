z2cb(double z)
{
    if (!Z_AXIS.log && !CB_AXIS.log)
	return z;
    if (Z_AXIS.log && !CB_AXIS.log)
	return exp(z * Z_AXIS.log_base);
    if (!Z_AXIS.log && CB_AXIS.log)
	return (z<=0) ? CB_AXIS.min : (log(z) / CB_AXIS.log_base);

    if (Z_AXIS.base==CB_AXIS.base)
	return z;
    return z * Z_AXIS.log_base / CB_AXIS.log_base;
}
