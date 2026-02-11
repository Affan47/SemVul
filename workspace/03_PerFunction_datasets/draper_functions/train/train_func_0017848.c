orth(const btVector3 &v)
{
	btVector3 a=btCross(v,btVector3(0,0,1));
	btVector3 b=btCross(v,btVector3(0,1,0));
	if (a.length() > b.length())
	{
		return a.normalized();
	} else {
		return b.normalized();
	}
}
