GetBondAtAngle (double angle)
{
	Bond *res = NULL, *bond;
	double a1, a0 = 2 * M_PI;
	std::map <gcu::Atom *, gcu::Bond *>::iterator it;
	for (bond = static_cast <gcp::Bond *> (GetFirstBond (it)); bond; bond = static_cast <gcp::Bond *> (GetNextBond (it))) {
		a1 = bond->GetAngle2DRad (this);
		a1 -= angle;
		a1 = fabs (a1);
		if (a1 > M_PI)
			a1 = 2 * M_PI - a1;
		if (a1 < a0) {
			a0 = a1;
			res = bond;
		}
	}
	return res;
}
