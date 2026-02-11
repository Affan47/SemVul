toXML(xmlNodePtr xml_parent_node) throw(FWException)
{
    if (getName().empty()) setName(getTypeName());

    xmlNodePtr me = FWObject::toXML(xml_parent_node);
    xmlNewProp(me, TOXMLCAST("name"), STRTOXMLCAST(getName()));
    xmlNewProp(me, TOXMLCAST("comment"), STRTOXMLCAST(getComment()));
    xmlNewProp(me, TOXMLCAST("ro"), TOXMLCAST(((getRO()) ? "True" : "False")));

    xmlNewProp(me,
               TOXMLCAST("address"),
               STRTOXMLCAST(inet_addr_mask->getAddressPtr()->toString()));

    xmlNewProp(me,
               TOXMLCAST("netmask"),
               STRTOXMLCAST(inet_addr_mask->getNetmaskPtr()->toString()));

    return me;
}
