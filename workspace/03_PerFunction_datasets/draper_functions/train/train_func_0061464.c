multKronTrans(KronVector& x) const
{
	int largest = getLargestBlock();
	Vector work(largest*x.getN()*power(x.getM(),x.getDepth()-1));
	const_diag_iter start = diag_begin();
	const_diag_iter end = findBlockStart(start);
	while (start != diag_end()) {
		multKronBlockTrans(start, end, x, work);
		start = end;
		end = findBlockStart(start);
	}
}
