Read(const wxString& name,  bool* value)
{
    wxString key(name);
    TiXmlElement* e = AssertPath(key);

    TiXmlHandle parentHandle(e);
    TiXmlElement *leaf = parentHandle.FirstChild(cbU2C(key)).Element();

    if (leaf && leaf->Attribute("bool"))
    {
        *value = leaf->Attribute("bool")[0] == '1';
        return true;
    }
    return false;
}
