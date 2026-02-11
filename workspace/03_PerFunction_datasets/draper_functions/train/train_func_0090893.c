GetStatusTextByPlugin(cbPlugin* plugin) const
{
    int pos = GetFieldNumberOfPlugin(plugin);
    if (pos != -1)
        return wxStatusBar::GetStatusText(pos);
    return wxEmptyString;
}
