DoEditTool(cbTool* tool)
{
    if (!tool)
        return false;
    EditToolDlg dlg(this, tool);
    PlaceWindow(&dlg);
    return dlg.ShowModal() == wxID_OK;
}
