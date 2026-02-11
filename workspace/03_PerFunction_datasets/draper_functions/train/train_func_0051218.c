insert(ParamStruct* ps) {
    ALIterator i;
    for (First(i); !Done(i); Next(i)) {
	ParamStruct* ops = GetStruct(i);
	if (ps->format() == ParamStruct::other) break;
	if (ps->format() == ParamStruct::required &&
	    ops->format() != ParamStruct::required) break;
	if (ps->format() == ParamStruct::optional &&
	    ops->format() == ParamStruct::keyword) break;
    }
    InsertBefore(i, ps);
    _count++;
    if (ps->format() == ParamStruct::required) _required_count++;
    if (ps->format() == ParamStruct::optional) _optional_count++;
    if (ps->format() == ParamStruct::keyword) _keyword_count++;
    if (ps->format() == ParamStruct::other) _other_count++;
}
