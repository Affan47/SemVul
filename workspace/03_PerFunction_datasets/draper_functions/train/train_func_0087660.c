GetUnitAlias(int alias, int faction)
{

	forlist((&units)) {
		if(((Unit *)elem)->alias == alias &&
				((Unit *)elem)->formfaction->num == faction)
			return ((Unit *)elem);
	}

	{
		forlist((&units)) {
			if (((Unit *) elem)->alias == alias &&
					((Unit *) elem)->faction->num == faction)
				return ((Unit *) elem);
		}
	}
	return 0;
}
