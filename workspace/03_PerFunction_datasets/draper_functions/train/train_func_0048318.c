ExtractString( CeosRecord_t *record, unsigned int offset, unsigned int length, char *string )
{
    char format[12];

    if(string == NULL)
    {
	string = HMalloc( length + 1 );
    }

    sprintf( format, "A%u", length );

    GetCeosField( record, offset, format, string );

    return string;
}
