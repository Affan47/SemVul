httpHdrRangeOffsetLimit(HttpHdrRange * range)
{
    if (NULL == range)

	return 0;
    if (!Config.rangeOffsetLimit)

	return 1;
    if (-1 == Config.rangeOffsetLimit)

	return 0;
    if (Config.rangeOffsetLimit >= httpHdrRangeFirstOffset(range))

	return 0;
    return 1;
}
