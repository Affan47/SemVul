fm_xml_file_insert_first(FmXmlFile *file, FmXmlFileItem *new_item)
{
    g_return_val_if_fail(file != NULL && FM_IS_XML_FILE(file), FALSE);
    g_return_val_if_fail(new_item != NULL, FALSE);
    if (_xml_item_is_busy(new_item))
        return FALSE;
    if (new_item->parent_list)
    {

        g_assert(new_item->file != NULL && g_list_find(*new_item->parent_list, new_item) != NULL);
        *new_item->parent_list = g_list_remove(*new_item->parent_list, new_item);
    }
    file->items = g_list_prepend(file->items, new_item);
    new_item->parent_list = &file->items;
    new_item->parent = NULL;
    if (new_item->file != file)
        _reassign_xml_file(new_item, file);
    return TRUE;
}
