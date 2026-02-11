obt_xml_instance_unref(ObtXmlInst *i)
{
    if (i && --i->ref == 0) {
        obt_paths_unref(i->xdg_paths);
        g_hash_table_destroy(i->callbacks);
        g_free(i->last_error_file);
        g_free(i->last_error_message);
        g_slice_free(ObtXmlInst, i);
    }
}
