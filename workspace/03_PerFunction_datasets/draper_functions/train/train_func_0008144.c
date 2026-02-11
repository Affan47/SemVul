Mask_Editor_List_Save_Button (void)
{
    Mask_Editor_Clean_Up_Masks_List();

    if (gtk_combo_box_get_active(GTK_COMBO_BOX(ScannerOptionCombo)) == SCANNER_FILL_TAG)
    {
        Save_Scan_Tag_Masks_List(ScanTagListModel, MASK_EDITOR_TEXT);
    } else if (gtk_combo_box_get_active(GTK_COMBO_BOX(ScannerOptionCombo)) == SCANNER_RENAME_FILE)
    {
        Save_Rename_File_Masks_List(RenameFileListModel, MASK_EDITOR_TEXT);
    }
}
