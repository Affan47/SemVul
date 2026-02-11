dna_is_multitype_range(struct configEntry *config_entry)
{
    int ret = 0;

    if (config_entry && config_entry->types && config_entry->types[1]) {
        ret = 1;
    }

    return ret;
}
