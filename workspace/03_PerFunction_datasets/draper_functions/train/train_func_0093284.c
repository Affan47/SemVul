deleteMedium(const DOM::DOMString &oldMedium)
{
    if(!impl)
        return;
    int exceptioncode = 0;
    ((MediaListImpl *)impl)->deleteMedium( oldMedium, exceptioncode );
    if ( exceptioncode )
        throw DOMException( exceptioncode );
}
