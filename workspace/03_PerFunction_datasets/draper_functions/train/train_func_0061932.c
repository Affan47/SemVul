toXML(xmlNodePtr parent) throw(FWException)
{
    xmlNodePtr me = RuleElement::toXML(parent);

    for(list<FWObject*>::const_iterator j=begin(); j!=end(); ++j)
        (*j)->toXML(me);

    return me;
}
