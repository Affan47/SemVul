changePermissionsRowCbk(GtkTreeModel* model, GtkTreePath* path,
                             GtkTreeIter* iterator, gpointer data)
{
    char* itemName;
    char* fullItemName;
    mode_t permissions;

    gtk_tree_model_get(model, iterator, COLUMN_FILENAME, &itemName, -1);

    fullItemName = malloc(strlen(GBLisoCurrentDir) + strlen(itemName) + 1);
    if(fullItemName == NULL)
        fatalError("changePermissionsRowCbk(): malloc("
                   "strlen(GBLisoCurrentDir) + strlen(itemName) + 1) failed (out of memory?)");

    strcpy(fullItemName, GBLisoCurrentDir);
    strcat(fullItemName, itemName);

    if(askForPermissions(fullItemName, &permissions))
    {
        bk_set_permissions(&GBLvolInfo, fullItemName, permissions);
        GBLisoChangesProbable = true;
    }

    g_free(itemName);
    free(fullItemName);
}
