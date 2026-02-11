toXML(xmlNodePtr parent) throw(FWException)
{
    xmlNodePtr me = FWObject::toXML(parent, false);
    xmlRemoveProp(xmlHasProp(me, TOXMLCAST("run_time")));
    xmlNewProp(me, TOXMLCAST("name"), STRTOXMLCAST(getName()));
    xmlNewProp(me, TOXMLCAST("comment"), STRTOXMLCAST(getComment()));
    xmlNewProp(me, TOXMLCAST("ro"), TOXMLCAST(((getRO()) ? "True" : "False")));

    list<string>::const_iterator iter;
    for (iter = m_filter.begin(); iter != m_filter.end(); ++iter) {
        string filter, type, keyword;
        if (!splitFilter(*iter, type, keyword)) continue;
        if (!makeFilter(filter, type, keyword)) continue;

        xmlNodePtr item = xmlNewChild(me, NULL,
                                      TOXMLCAST("SelectionCriteria"), NULL);
        xmlNewProp(item, TOXMLCAST("type"), STRTOXMLCAST(type));
        xmlNewProp(item, TOXMLCAST("keyword"), STRTOXMLCAST(keyword));
    }

    return me;
}
