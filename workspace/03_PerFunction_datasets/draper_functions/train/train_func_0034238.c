ET_Free_History_File_List (void)
{
    g_return_val_if_fail (ETCore != NULL && ETCore->ETHistoryFileList != NULL,
                          FALSE);

    ETCore->ETHistoryFileList = g_list_first (ETCore->ETHistoryFileList);

    g_list_free_full (ETCore->ETHistoryFileList, g_free);

    ETCore->ETHistoryFileList = NULL;

    return TRUE;
}
