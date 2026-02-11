menus_sensitifs ( gboolean sensitif )
{
    gchar * items[] = {
    menu_name ( "FileMenu",     "Save",                 NULL ),
    menu_name ( "FileMenu",     "SaveAs",               NULL ),
    menu_name ( "FileMenu",     "DebugFile",            NULL ),
    menu_name ( "FileMenu",     "Obfuscate",            NULL ),
    menu_name ( "FileMenu",     "DebugMode",            NULL ),
    menu_name ( "FileMenu",     "ExportFile",           NULL ),
    menu_name ( "FileMenu",     "CreateArchive",        NULL ),
    menu_name ( "FileMenu",     "ExportArchive",        NULL ),
    menu_name ( "FileMenu",     "Close",                NULL ),
    menu_name ( "EditMenu",     "NewTransaction",       NULL ),
    menu_name ( "EditMenu",     "RemoveTransaction",    NULL ),
    menu_name ( "EditMenu",     "CloneTransaction",     NULL ),
    menu_name ( "EditMenu",     "EditTransaction",      NULL ),
    menu_name ( "EditMenu",     "ConvertToScheduled",   NULL ),
    menu_name ( "EditMenu",     "MoveToAnotherAccount", NULL ),
    menu_name ( "EditMenu",     "Preferences",          NULL ),
    menu_name ( "EditMenu",     "RemoveAccount",        NULL ),
    menu_name ( "EditMenu",     "NewAccount",           NULL ),
    menu_name ( "ViewMenu",     "ShowTransactionForm",  NULL ),
    menu_name ( "ViewMenu",     "ShowGrid",             NULL ),
    menu_name ( "ViewMenu",     "ShowReconciled",       NULL ),
    menu_name ( "ViewMenu",     "ShowArchived",         NULL ),
    menu_name ( "ViewMenu",     "ShowClosed",           NULL ),
    menu_name ( "ViewMenu",     "ShowOneLine",          NULL ),
    menu_name ( "ViewMenu",     "ShowTwoLines",         NULL ),
    menu_name ( "ViewMenu",     "ShowThreeLines",       NULL ),
    menu_name ( "ViewMenu",     "ShowFourLines",        NULL ),
    menu_name ( "ViewMenu",     "InitwidthCol",        NULL ),
    NULL,
    };
    gchar ** tmp = items;

    devel_debug_int (sensitif);

    while ( *tmp )
    {
    gsb_gui_sensitive_menu_item_from_string ( *tmp, sensitif );
    tmp++;
    }


    gsb_gui_sensitive_menu_item ( "EditMenu", "NewTransaction", NULL, FALSE );
    gsb_menu_transaction_operations_set_sensitive ( FALSE );
}
