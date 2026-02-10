is_primary_selection(ED4_terminal *object )
{
    ED4_list_elem        *tmp_elem;
    ED4_selection_entry  *tmp_entry;

    tmp_elem = ( ED4_list_elem *) selected_objects.last();
    if (!tmp_elem) return 0;

    tmp_entry = ( ED4_selection_entry *) tmp_elem->elem();
    return (tmp_entry != NULL) && (tmp_entry->object == object);
}
