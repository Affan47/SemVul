multaVecTrans(Vector& x, const ConstVector& b) const
{
	ConstVector bu(b, 0, b.length());
	ConstVector bl(b, nz, b.length()-nz);
	Vector xu(x, 0, nz);
	Vector xl(x, nz, x.length()-nz);
	xu.zeros();
	QuasiTriangular::multVecTrans(xl, bl);
	ru.multaVecTrans(xl, bu);
}
