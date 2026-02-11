Read(const wxString& name, wxColour* ret)
{
    wxString key(name);
    TiXmlElement* e = AssertPath(key);

    TiXmlHandle parentHandle(e);
    TiXmlElement *c = (TiXmlElement *) parentHandle.FirstChild(cbU2C(key)).FirstChild("colour").Element();

    if (c)
    {
        int r, g, b;
        if (c->QueryIntAttribute("r", &r) == TIXML_SUCCESS
                && c->QueryIntAttribute("g", &g) == TIXML_SUCCESS
                && c->QueryIntAttribute("b", &b) == TIXML_SUCCESS)
            ret->Set(r, g, b);
        return true;
    }
    return false;
}
