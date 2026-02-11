jsonProperties(JsonOut *json)
{
    Dsymbol::jsonProperties(json);

    json->propertyStorageClass("storageClass", storage_class);

    json->property("type", "deco", type);


    if (type != originalType && originalType)
    {
        const char *ostr = originalType->toChars();
        if (type)
        {   const char *tstr = type->toChars();
            if (strcmp(tstr, ostr))
            {

                json->property("originalType", ostr);
            }
        }
        else
            json->property("originalType", ostr);
    }
}
