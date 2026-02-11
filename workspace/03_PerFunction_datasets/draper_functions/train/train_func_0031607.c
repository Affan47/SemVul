setValue(const wxString& key, const wxString& value)
{
    bool result = getConfig()->Write(key, value);
    if (!isLocked())
        getConfig()->Flush();
    else
        needsFlushM = true;
    notifyObservers();
    return result;
}
