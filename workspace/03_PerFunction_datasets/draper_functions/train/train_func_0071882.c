length() const
{
    if ( impl )
	return ((CharacterDataImpl *)impl)->length();
    return 0;
}
