dbmap_count(const dbmap_t *dm)
{
	dbmap_check(dm);

	if (DBMAP_MAP == dm->type) {
		size_t count = map_count(dm->u.m.map);
		g_assert(dm->count == count);
	}

	return dm->count;
}
