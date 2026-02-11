xmlnode_save_file(xmlnode *root, const gchar *filepath)
{
    g_return_val_if_fail(root != NULL, HYBRID_ERROR);
    g_return_val_if_fail(root->is_root == 1, HYBRID_ERROR);
    g_return_val_if_fail(filepath != NULL, HYBRID_ERROR);

    if (xmlSaveFormatFileEnc(filepath, root->doc, "UTF-8", 0) == -1) {
        return HYBRID_ERROR;
    }

    return HYBRID_OK;
}
