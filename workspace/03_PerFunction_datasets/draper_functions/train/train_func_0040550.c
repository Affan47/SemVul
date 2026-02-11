beta_multiply_f()
{
	int beta_pow = ogp::OperationTree::one;
	for (int ll = 0; ll <= maxlead; ll++,
			 beta_pow = model.eqs.add_binary(ogp::DIVIDE, beta_pow, tbeta))
		for (int yi = 0; yi < diff_f.dim1(); yi++)
			for (int fi = 0; fi < diff_f.dim2(); fi++)
				if (diff_f(yi, fi, ll-minlag) != ogp::OperationTree::zero)
					diff_f(yi, fi, ll-minlag) =
						model.eqs.add_binary(ogp::TIMES, beta_pow, diff_f(yi, fi, ll-minlag));

	beta_pow = ogp::OperationTree::one;
	for (int ll = 0; ll >= minlag; ll--,
			 beta_pow = model.eqs.add_binary(ogp::TIMES, beta_pow, tbeta))
		for (int yi = 0; yi < diff_f.dim1(); yi++)
			for (int fi = 0; fi < diff_f.dim2(); fi++)
				if (diff_f(yi, fi, ll-minlag) != ogp::OperationTree::zero)
					diff_f(yi, fi, ll-minlag) =
						model.eqs.add_binary(ogp::TIMES, beta_pow, diff_f(yi, fi, ll-minlag));
}
