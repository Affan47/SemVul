gist_point_consistent(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	StrategyNumber strategy = (StrategyNumber) PG_GETARG_UINT16(2);
	bool	   *recheck = (bool *) PG_GETARG_POINTER(4);
	bool		result;
	StrategyNumber strategyGroup = strategy / GeoStrategyNumberOffset;

	switch (strategyGroup)
	{
		case PointStrategyNumberGroup:
			result = gist_point_consistent_internal(strategy % GeoStrategyNumberOffset,
													GIST_LEAF(entry),
													DatumGetBoxP(entry->key),
													PG_GETARG_POINT_P(1));
			*recheck = false;
			break;
		case BoxStrategyNumberGroup:
			result = DatumGetBool(DirectFunctionCall5(
													  gist_box_consistent,
													  PointerGetDatum(entry),
													  PG_GETARG_DATUM(1),
									  Int16GetDatum(RTOverlapStrategyNumber),
											   0, PointerGetDatum(recheck)));
			break;
		case PolygonStrategyNumberGroup:
			{
				POLYGON    *query = PG_GETARG_POLYGON_P(1);

				result = DatumGetBool(DirectFunctionCall5(
														gist_poly_consistent,
													  PointerGetDatum(entry),
													 PolygonPGetDatum(query),
									  Int16GetDatum(RTOverlapStrategyNumber),
											   0, PointerGetDatum(recheck)));

				if (GIST_LEAF(entry) && result)
				{


					BOX		   *box = DatumGetBoxP(entry->key);

					Assert(box->high.x == box->low.x
						   && box->high.y == box->low.y);
					result = DatumGetBool(DirectFunctionCall2(
															  poly_contain_pt,
													 PolygonPGetDatum(query),
												PointPGetDatum(&box->high)));
					*recheck = false;
				}
			}
			break;
		case CircleStrategyNumberGroup:
			{
				CIRCLE	   *query = PG_GETARG_CIRCLE_P(1);

				result = DatumGetBool(DirectFunctionCall5(
													  gist_circle_consistent,
													  PointerGetDatum(entry),
													  CirclePGetDatum(query),
									  Int16GetDatum(RTOverlapStrategyNumber),
											   0, PointerGetDatum(recheck)));

				if (GIST_LEAF(entry) && result)
				{


					BOX		   *box = DatumGetBoxP(entry->key);

					Assert(box->high.x == box->low.x
						   && box->high.y == box->low.y);
					result = DatumGetBool(DirectFunctionCall2(
														   circle_contain_pt,
													  CirclePGetDatum(query),
												PointPGetDatum(&box->high)));
					*recheck = false;
				}
			}
			break;
		default:
			elog(ERROR, "unknown strategy number: %d", strategy);
			result = false;
	}

	PG_RETURN_BOOL(result);
}
