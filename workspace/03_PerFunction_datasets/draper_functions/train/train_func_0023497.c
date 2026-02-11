get( EVCard* c, const char* v )
{
    EVCardAttribute* a = e_vcard_get_attribute( c, v );
    UT_DEBUGMSG((" cvard.group:%s v:%s\n", e_vcard_attribute_get_group( a ), v ));

    if( a && e_vcard_attribute_is_single_valued(a) )
    {
        return e_vcard_attribute_get_value(a);
    }
    return "";
}
