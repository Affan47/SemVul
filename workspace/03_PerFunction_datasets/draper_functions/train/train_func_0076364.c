setAttr(const std::string &attr, const Element &val)
{
    beginUpdate();


    const Element* typeElement(0);
    AttrMap::const_iterator A = m_attrs.find(attr);
    if (A == m_attrs.end() && m_type) {

        typeElement = m_type->getAttribute(attr);
    }


    const Element* newElement(0);

    if (A == m_attrs.end() && typeElement == 0) {
        std::pair<AttrMap::const_iterator, bool> I = m_attrs.insert(AttrMap::value_type(attr, val));
        newElement = &(I.first->second);
    } else {

        Element& target = m_attrs[attr];

        newElement = &target;
        if (A == m_attrs.end()) {

            target = *typeElement;
        }
        mergeOrCopyElement(val, target);

    }
    nativeAttrChanged(attr, *newElement);
    onAttrChanged(attr, *newElement);


    ObserverMap::const_iterator obs = m_observers.find(attr);
    if (obs != m_observers.end()) {
        obs->second.emit(*newElement);
    }

    addToUpdate(attr);
    endUpdate();
}
