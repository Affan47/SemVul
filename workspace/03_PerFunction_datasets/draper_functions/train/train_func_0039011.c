GetPath() const
{
    TiXmlElement *e = pathNode;
    wxString ret;
    ret.Alloc(64);

    ret = cbC2U(e->Value());
    while ((e = e->Parent()->ToElement()) && e != root)
    {
        ret.Prepend(_T('/'));
        ret.Prepend(cbC2U(e->Value()));
    }
    ret.Prepend(_T('/'));
    return ret;
}
