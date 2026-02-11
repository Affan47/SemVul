emulate_f2l(float value)
{
	if (finitef(value)) {
		if (value >= J_LONG_MAX)
			return J_LONG_MAX;
		if (value <= J_LONG_MIN)
			return J_LONG_MIN;

		return value;
	}

	if (isnanf(value))
		return 0;

	if (copysignf(1.0, value) > 0)
		return J_LONG_MAX;

	return J_LONG_MIN;
}
