make_local_array_table(const Array_def_use_table_semnode *local_du,
                       Array_table *ahead,
                       int offset,
                       memory_kind kind)
{
    const Array_def_use_table_semnode *apt;
    Array_table *ltbl, *head = NULL;
    int toffset = offset;

    for (apt = local_du; apt != NULL; apt = apt->next) {
        Array_table *ctbl = search_array_table(ahead, apt->entry);
        toffset += toffset % byte2word(get_element_byte_size(ctbl->type,
                                                             ctbl->type_entry));
        ltbl = get_local_array_table(apt, ctbl, &toffset, kind);
        append_array_table(&head, ltbl);
    }

    return head;
}
