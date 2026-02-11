replaceData( const unsigned long offset, const unsigned long count, const DOMString &arg )
{
    if (!impl)
	return;

    int exceptioncode = 0;
    ((CharacterDataImpl *)impl)->replaceData(offset, count, arg, exceptioncode);
    if ( exceptioncode )
	throw DOMException( exceptioncode );
}
