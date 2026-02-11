PR_ErrorInstallTable(const struct PRErrorTable *table)
{
    struct PRErrorTableList * new_et;

    new_et = (struct PRErrorTableList *)
					PR_Malloc(sizeof(struct PRErrorTableList));
    if (!new_et)
	return errno;
    new_et->table = table;
    if (callback_newtable) {
	new_et->table_private = callback_newtable(table, callback_private);
    } else {
	new_et->table_private = 0;
    }
    new_et->next = Table_List;
    Table_List = new_et;
    return 0;
}
