FillScan(ILint scan, Edge *active)
{
	Edge *p1, *p2;
	ILint i;

	p1 = active->next;
	while (p1) {
		p2 = p1->next;
		for (i = (ILuint)p1->xIntersect; i < p2->xIntersect; i++) {
			iRegionSetPixel((ILuint)i, scan);
		}
		p1 = p2->next;
	}
}
