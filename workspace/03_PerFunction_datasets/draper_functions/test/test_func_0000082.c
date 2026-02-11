setSelectionRange(long start, long end)
{
    if (impl)
	((HTMLInputElementImpl *)impl)->setSelectionRange( start, end );
}
