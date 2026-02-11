get_distance(TypeCacheEntry *typcache, RangeBound *bound1, RangeBound *bound2)
{
	bool		has_subdiff = OidIsValid(typcache->rng_subdiff_finfo.fn_oid);

	if (!bound1->infinite && !bound2->infinite)
	{


		if (has_subdiff)
			return
				DatumGetFloat8(FunctionCall2Coll(&typcache->rng_subdiff_finfo,
												 typcache->rng_collation,
												 bound2->val,
												 bound1->val));
		else
			return 1.0;
	}
	else if (bound1->infinite && bound2->infinite)
	{

		if (bound1->lower == bound2->lower)
			return 0.0;
		else
			return get_float8_infinity();
	}
	else
	{

		return get_float8_infinity();
	}
}
