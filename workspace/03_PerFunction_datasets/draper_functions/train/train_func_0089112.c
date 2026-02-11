httpHdrRangeGetSpec(const HttpHdrRange * range, HttpHdrRangePos * pos)
{
    assert(range);
    assert(pos && *pos >= -1 && *pos < range->specs.count);
    (*pos)++;
    if (*pos < range->specs.count)
	return (HttpHdrRangeSpec *) range->specs.items[*pos];
    else
	return NULL;
}
