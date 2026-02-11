mp4ff_tag_delete(mp4ff_metadata_t *tags)
{
    uint32_t i;

    for (i = 0; i < tags->count; i++)
    {
        if (tags->tags[i].item) free(tags->tags[i].item);
        if (tags->tags[i].value) free(tags->tags[i].value);
    }

    if (tags->tags) free(tags->tags);

    tags->tags = NULL;
    tags->count = 0;

    return 0;
}
