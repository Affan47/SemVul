af9013_div(struct af9013_state *state, u32 a, u32 b, u32 x)
{
	u32 r = 0, c = 0, i;

	dev_dbg(&state->i2c->dev, "%s: a=%d b=%d x=%d\n", __func__, a, b, x);

	if (a > b) {
		c = a / b;
		a = a - c * b;
	}

	for (i = 0; i < x; i++) {
		if (a >= b) {
			r += 1;
			a -= b;
		}
		a <<= 1;
		r <<= 1;
	}
	r = (c << (u32)x) + r;

	dev_dbg(&state->i2c->dev, "%s: a=%d b=%d x=%d r=%d r=%x\n",
			__func__, a, b, x, r, r);

	return r;
}
