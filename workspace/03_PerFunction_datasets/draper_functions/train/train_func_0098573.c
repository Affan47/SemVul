toXML(xmlNodePtr xml_parent_node) throw(FWException)
{
    xmlNodePtr me = FWObject::toXML(xml_parent_node);

    xmlNewProp(me, TOXMLCAST("name"), STRTOXMLCAST(getName()));
    xmlNewProp(me, TOXMLCAST("comment"), STRTOXMLCAST(getComment()));
    xmlNewProp(me, TOXMLCAST("ro"), TOXMLCAST(((getRO()) ? "True" : "False")));

    xmlNewProp(me,
               TOXMLCAST("start_address"),
               STRTOXMLCAST(start_address.toString()));

    xmlNewProp(me,
               TOXMLCAST("end_address"),
               STRTOXMLCAST(end_address.toString()));

    return me;
}
