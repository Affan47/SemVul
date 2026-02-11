Read(const wxString& name, wxString* str)
{
    if (name.IsSameAs(CfgMgrConsts::app_path))
    {
        str->assign(app_path);
        return true;
    }
    else if (name.IsSameAs(CfgMgrConsts::data_path))
    {
        str->assign(data_path_global);
        return true;
    }

    wxString key(name);
    TiXmlElement* e = AssertPath(key);

    TiXmlHandle parentHandle(e);
    TiXmlText *t = (TiXmlText *) parentHandle.FirstChild(cbU2C(key)).FirstChild("str").FirstChild().Node();

    if (t)
    {
        str->assign(cbC2U(t->Value()));
        return true;
    }
    return false;
}
