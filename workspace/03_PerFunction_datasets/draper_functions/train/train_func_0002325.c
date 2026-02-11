attrChangedFromTypeInfo(const std::string& attributeName, const Atlas::Message::Element& element)
{

    if (m_attrs.count(attributeName) == 0) {
        beginUpdate();
        nativeAttrChanged(attributeName, element);
        onAttrChanged(attributeName, element);


        ObserverMap::const_iterator obs = m_observers.find(attributeName);
        if (obs != m_observers.end()) {
            obs->second.emit(element);
        }

        addToUpdate(attributeName);
        endUpdate();
    }
}
