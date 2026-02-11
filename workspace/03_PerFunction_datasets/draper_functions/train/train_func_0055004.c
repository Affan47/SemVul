Maximize(Box *cube, ILubyte dir, ILint first, ILint last, ILint *cut,
				 ILint whole_r, ILint whole_g, ILint whole_b, ILint whole_w)
{
	ILint	half_r, half_g, half_b, half_w;
	ILint	base_r, base_g, base_b, base_w;
	ILint	i;
	ILfloat	temp, max;

	base_r = Bottom(cube, dir, mr);
	base_g = Bottom(cube, dir, mg);
	base_b = Bottom(cube, dir, mb);
	base_w = Bottom(cube, dir, wt);
	max = 0.0;
	*cut = -1;

	for (i = first; i < last; ++i) {
		half_r = base_r + Top(cube, dir, i, mr);
		half_g = base_g + Top(cube, dir, i, mg);
		half_b = base_b + Top(cube, dir, i, mb);
		half_w = base_w + Top(cube, dir, i, wt);

		if (half_w == 0) {
			continue;
		}
		else {
			temp = ((ILfloat)half_r*half_r + (ILfloat)half_g * half_g +
					(ILfloat)half_b*half_b) / half_w;
		}

		half_r = whole_r - half_r;
		half_g = whole_g - half_g;
		half_b = whole_b - half_b;
		half_w = whole_w - half_w;
		if (half_w == 0) {
			continue;
		}
		else {
			temp += ((ILfloat)half_r*half_r + (ILfloat)half_g * half_g +
					(ILfloat)half_b*half_b) / half_w;
		}

		if (temp > max) {
			max = temp;
			*cut = i;
		}
	}

	return max;
}
