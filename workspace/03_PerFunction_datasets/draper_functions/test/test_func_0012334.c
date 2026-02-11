getPropertyAttributes(const Identifier& propertyName, unsigned int& attributes) const
{
    size_t index = symbolTable->get(propertyName.ustring().rep());
    if (index != missingSymbolMarker()) {
        LocalStorageEntry& entry = localStorage[index];
        attributes = entry.attributes;
        return true;
    }

    return JSVariableObject::getPropertyAttributes(propertyName, attributes);
}
