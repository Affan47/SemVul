free_entry_list(struct ucftpentry *list)
{
    while(list != NULL) {
        struct ucftpentry *ent = list;
        list = list->next;

        list_remove_entry(ent);
        ucftp_free_tree(ent);
    }
}
