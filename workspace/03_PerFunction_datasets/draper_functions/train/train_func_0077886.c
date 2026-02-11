FreeCVTableList(Const_var_table *head)
{
    Const_var_table *currData;
    Const_var_table *reserved = NULL;

    currData = head;
    while (currData != NULL) {
	reserved = currData->next;
	FreeConstVarTable(currData);
	currData = reserved;
    }
}
