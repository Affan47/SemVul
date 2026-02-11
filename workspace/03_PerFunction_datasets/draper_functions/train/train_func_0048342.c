FcStrSerialize (FcSerialize *serialize, const FcChar8 *str)
{
    FcChar8 *str_serialize = FcSerializePtr (serialize, str);
    if (!str_serialize)
	return NULL;
    strcpy ((char *) str_serialize, (const char *) str);
    return str_serialize;
}
