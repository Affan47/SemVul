amglue_source_get(
    GSource *gsrc,
    GSourceFunc callback)
{
    amglue_Source *src;
    g_assert(gsrc != NULL);

    src = (amglue_Source *)g_dataset_id_get_data(gsrc, AMGLUE_SOURCE_QUARK);

    if (!src)
	src = amglue_source_new(gsrc, callback);
    else
	amglue_source_ref(src);

    return src;
}
