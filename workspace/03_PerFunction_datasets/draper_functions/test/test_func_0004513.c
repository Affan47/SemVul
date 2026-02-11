inlineApplySortFunction(FmgrInfo *sortFunction, SortFunctionKind kind,
						Datum datum1, bool isNull1,
						Datum datum2, bool isNull2)
{
	switch (kind)
	{
		case SORTFUNC_LT:
			if (isNull1)
			{
				if (isNull2)
					return 0;
				return 1;
			}
			if (isNull2)
				return -1;
			if (DatumGetBool(myFunctionCall2(sortFunction, datum1, datum2)))
				return -1;
			if (DatumGetBool(myFunctionCall2(sortFunction, datum2, datum1)))
				return 1;
			return 0;

		case SORTFUNC_REVLT:

			if (isNull1)
			{
				if (isNull2)
					return 0;
				return -1;
			}
			if (isNull2)
				return 1;
			if (DatumGetBool(myFunctionCall2(sortFunction, datum1, datum2)))
				return -1;
			if (DatumGetBool(myFunctionCall2(sortFunction, datum2, datum1)))
				return 1;
			return 0;

		case SORTFUNC_CMP:
			if (isNull1)
			{
				if (isNull2)
					return 0;
				return 1;
			}
			if (isNull2)
				return -1;
			return DatumGetInt32(myFunctionCall2(sortFunction,
												 datum1, datum2));

		case SORTFUNC_REVCMP:
			if (isNull1)
			{
				if (isNull2)
					return 0;
				return -1;
			}
			if (isNull2)
				return 1;
			return -DatumGetInt32(myFunctionCall2(sortFunction,
												  datum1, datum2));

		default:
			elog(ERROR, "unrecognized SortFunctionKind: %d", (int) kind);
			return 0;
	}
}
