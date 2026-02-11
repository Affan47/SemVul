WriteElement(string sSection, string sEntry,
                             string fn, string sValue)
{
    if (0 == fn.length())
        return false;

    IniFile MyIniFile (fn);

    MyIniFile.SetKeyValue(sSection, sEntry, sValue);
    return true;
}
