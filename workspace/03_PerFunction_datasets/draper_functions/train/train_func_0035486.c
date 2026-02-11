DoAddPluginStatusField(cbPlugin* plugin)
{
    cbStatusBar *sbar = (cbStatusBar *)GetStatusBar();
    if (!sbar)
        return;
    plugin->CreateStatusField(sbar);
    sbar->AdjustFieldsSize();
}
