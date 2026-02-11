setMatrixViaIter(double r, const QuasiTriangular& t)
{
	register double rr = r;
	diag_iter dil = diag_begin();
	const_diag_iter dir = t.diag_begin();
	for ( ; dil != diag_end(); ++dil, ++dir) {
		(*dil).getAlpha() = rr*(*(*dir).getAlpha());
		if (! (*dil).isReal()) {
			(*dil).getBeta1() = rr*(*dir).getBeta1();
			(*dil).getBeta2() = rr*(*dir).getBeta2();
		}
		col_iter cil = col_begin(*dil);
		const_col_iter cir = t.col_begin(*dir);
		for ( ; cil != col_end(*dil); ++cil, ++cir) {
			if ((*dil).isReal()) {
				*cil = rr*(*cir);
			} else {
				cil.a() = rr*cir.a();
				cil.b() = rr*cir.b();
			}
		}
	}
}
