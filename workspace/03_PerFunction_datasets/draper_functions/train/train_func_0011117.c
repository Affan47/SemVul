add_until( Poly *polyp, const Point &point, DirPolyIter &dpi )
{
	do
	{
		polyp->add(dpi.point());
		dpi.next();
	} while(dpi.point() != point);
}
