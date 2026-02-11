RemoveProperty(NPIdentifier name)
{
    std::map<NPIdentifier, GnashNPVariant>::iterator it;
    it = _properties.find(name);
    if (it != _properties.end()) {
        _properties.erase(it);
        return true;
    }

    return false;
}
