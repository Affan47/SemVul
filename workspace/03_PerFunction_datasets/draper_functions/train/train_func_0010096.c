areacount(area_s *p, int &c, Object **startend)
{
	if (p) {
		areacount(p->left, c, startend);
		if (!*startend || p->start->compareTo(*startend) != 0) c++;
		*startend = p->end;
		areacount(p->right, c, startend);
	}
}
