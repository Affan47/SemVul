getPropertyAttributes(const Identifier& propertyName, unsigned int& attributes) const
{
    bool isArrayIndex;
    unsigned i = propertyName.toArrayIndex(&isArrayIndex);

    if (isArrayIndex) {
        ArrayEntity* ent = getArrayEntity(i);
        if (ent) {
            attributes = ent->attributes;
            return true;
        }
    }

    return KJS::JSObject::getPropertyAttributes(propertyName, attributes);
}
