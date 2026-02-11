slist_test_traverse(gpointer data, gpointer user_data){
    register gchar *word = data;
    SList_TestInfo *sti = user_data;
    g_message("Word [%5s] crib[%5s] count[%d]",
              word, sti->crib[sti->count], sti->count);
    g_assert(!strcmp(word, sti->crib[sti->count]));
    sti->count++;
    return FALSE;
    }
