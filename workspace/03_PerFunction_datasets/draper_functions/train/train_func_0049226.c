mp4ff_tag_set_field(mp4ff_metadata_t *tags, const char *item, const char *value)
{
    unsigned int i;

    if (!item || (item && !*item) || !value) return 0;

    for (i = 0; i < tags->count; i++)
    {
        if (!stricmp(tags->tags[i].item, item))
        {
			free(tags->tags[i].value);
			tags->tags[i].value = strdup(value);
			tags->tags[i].value_length = strlen(value);
            return 1;
        }
    }

    return mp4ff_tag_add_field(tags, item, value);
}
