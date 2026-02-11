sl2c_to_proj(s, p)
sl2c_matrix	s;
proj_matrix	p;
{
	int			j;
	sl2c_matrix	ad_s,
				fs,
				temp;
	static sl2c_matrix	m[4] = {{{{ 0.0, 0.0},{ 0.0, 1.0}},
								 {{ 0.0,-1.0},{ 0.0, 0.0}}},

								{{{ 0.0, 0.0},{ 1.0, 0.0}},
								 {{ 1.0, 0.0},{ 0.0, 0.0}}},

								{{{-1.0, 0.0},{ 0.0, 0.0}},
								 {{ 0.0, 0.0},{ 1.0, 0.0}}},

								{{{ 1.0, 0.0},{ 0.0, 0.0}},
								 {{ 0.0, 0.0},{ 1.0, 0.0}}}};

	for (j=0; j<4; j++) {
		sl2c_adjoint(s, ad_s);
		sl2c_mult(s, m[j], temp);
		sl2c_mult(temp, ad_s, fs);
		p[0][j] = fs[0][1].imag;
		p[1][j] = fs[0][1].real;
		p[2][j] = 0.5 * (fs[1][1].real - fs[0][0].real);
		p[3][j] = 0.5 * (fs[1][1].real + fs[0][0].real);
	}

	return;
}
