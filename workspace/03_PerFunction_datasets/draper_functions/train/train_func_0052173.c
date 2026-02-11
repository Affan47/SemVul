DEH_SetMapping(deh_context_t *context, deh_mapping_t *mapping,
                       void *structptr, char *name, int value)
{
    deh_mapping_entry_t *entry;
    void *location;

    entry = GetMappingEntryByName(context, mapping, name);

    if (entry == NULL)
    {
        return false;
    }


    if (entry->is_string)
    {
        DEH_Error(context, "Tried to set '%s' as integer (BUG)", name);
        return false;
    }

    location = GetStructField(structptr, mapping, entry);


    switch (entry->size)
    {
        case 1:
            * ((uint8_t *) location) = value;
            break;
        case 2:
            * ((uint16_t *) location) = value;
            break;
        case 4:
            * ((uint32_t *) location) = value;
            break;
        default:
            DEH_Error(context, "Unknown field type for '%s' (BUG)", name);
            return false;
    }

    return true;
}
