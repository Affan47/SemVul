toXML(xmlNodePtr parent) throw(FWException)
{
    xmlNodePtr me = FWObject::toXML(parent);
    xmlNewProp(me, TOXMLCAST("name"), STRTOXMLCAST(getName()));
    xmlNewProp(me, TOXMLCAST("comment"), STRTOXMLCAST(getComment()));
    xmlNewProp(me, TOXMLCAST("ro"), TOXMLCAST(((getRO()) ? "True" : "False")));

    xmlNewProp(me, TOXMLCAST("userid"), STRTOXMLCAST(userid));
    return me;
}
