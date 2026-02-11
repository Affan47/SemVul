toXML(xmlNodePtr parent) throw(FWException)
{
    xmlNodePtr me = FWObject::toXML(parent, false);
    xmlNewProp(me, TOXMLCAST("name"), STRTOXMLCAST(getName()));
    xmlNewProp(me, TOXMLCAST("comment"), STRTOXMLCAST(getComment()));
    xmlNewProp(me, TOXMLCAST("ro"), TOXMLCAST(((getRO()) ? "True" : "False")));

    FWObject *o;

    for(FWObjectTypedChildIterator j=findByType(Interface::TYPENAME); j!=j.end(); ++j)
 	if((o=(*j))!=NULL )
 	    o->toXML(me);

    o=getFirstByType( Management::TYPENAME );
    if (o) o->toXML(me);

    o=getFirstByType( HostOptions::TYPENAME );
    if (o) o->toXML(me);

    return me;
}
