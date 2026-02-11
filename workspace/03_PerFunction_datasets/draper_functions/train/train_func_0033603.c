setDefaultOption(FWObject *o,const string &xml_node)
{
    xmlNodePtr pn = XMLTools::getXmlNodeByPath(root,xml_node.c_str());
    if (pn==NULL) return;

    string optname=FROMXMLCAST(pn->name);
    string optval =getXmlNodeContent(pn);
    o->setStr(optname , optval);
}
