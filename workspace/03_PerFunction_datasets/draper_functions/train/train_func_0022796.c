Delete()
{
    CfgMgrBldr * bld = CfgMgrBldr::Get();
    wxString ns(cbC2U(root->Value()));

    root->Clear();
    doc->RootElement()->RemoveChild(root);

    wxCriticalSectionLocker(bld->cs);
    NamespaceMap::iterator it = bld->namespaces.find(ns);
    if (it != bld->namespaces.end())
        bld->namespaces.erase(it);

    delete this;
}
