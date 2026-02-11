httpHdrRangePackInto(const HttpHdrRange * range, Packer * p)
{
    HttpHdrRangePos pos = HttpHdrRangeInitPos;
    const HttpHdrRangeSpec *spec;
    assert(range);
    while ((spec = httpHdrRangeGetSpec(range, &pos))) {
	if (pos != HttpHdrRangeInitPos)
	    packerAppend(p, ",", 1);
	httpHdrRangeSpecPackInto(spec, p);
    }
}
