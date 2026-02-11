setAttributes(Root &obj,
                                        const Element& melem,
                                        std::set<std::string> used_attributes)
{
    MapType::const_iterator I;
    for (I = melem.asMap().begin(); I != melem.asMap().end(); I++) {
        std::set<std::string>::const_iterator attr_found =
                               used_attributes.find(I->first);
        if (attr_found == used_attributes.end()) {

            obj->setAttr(I->first, I->second);

        }
        used_attributes.insert(I->first);
    }
    I = melem.asMap().find(Atlas::Objects::PARENTS_ATTR);
    if (I != melem.asMap().end()) {
        for (ListType::const_iterator J = I->second.asList().begin();
             J != I->second.asList().end(); J++) {

            const Element & parent_melem = getMessageElement(J->asString());
            setAttributes(obj,  parent_melem, used_attributes);
        }
    }
}
