refers_to(Var target, Var key)
{
	int i;
	Var *p;

	switch((int) target.type) {
	case TYPE_LIST:
		if (target.v.list == key.v.list)
			return 1;
		for (i = 1; i <= target.v.list[0].v.num; ++i)
			if (refers_to(target.v.list[i], key))
				return 1;
		return 0;
	case TYPE_WAIF:
		if (target.v.waif == key.v.waif)
			return 1;
		p = target.v.waif->propvals;
		i = count_waif_propvals(target.v.waif);
		while (i-- > 0)
			if (refers_to(*p++, key))
				return 1;
		return 0;
	case TYPE_FLOAT:
		return target.v.fnum == key.v.fnum;
	case TYPE_STR:
		return target.v.str == key.v.str;
	}
	return 0;
}
