FcVStackPushRange (FcConfigParse *parse, FcRange *range)
{
    FcVStack	*vstack = FcVStackCreateAndPush (parse);
    if (!vstack)
	return FcFalse;
    vstack->u.range.begin = range->begin;
    vstack->u.range.end = range->end;
    vstack->tag = FcVStackRange;
    return FcTrue;
}
