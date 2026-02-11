maybeInitRetainerSet( StgClosure *c )
{
    if (!isRetainerSetFieldValid(c)) {
	setRetainerSetToNull(c);
    }
}
