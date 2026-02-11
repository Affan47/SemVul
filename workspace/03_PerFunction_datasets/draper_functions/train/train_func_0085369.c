unwatch(const ObjectURI& uri)
{
    if (!_trigs.get()) return false;

    TriggerContainer::iterator trigIter = _trigs->find(uri);
    if (trigIter == _trigs->end()) {
        log_debug("No watch for property %s",
                  getStringTable(*this).value(getName(uri)));
        return false;
    }
    Property* prop = _members.getProperty(uri);
    if (prop && prop->isGetterSetter()) {
        log_debug("Watch on %s not removed (is a getter-setter)",
                  getStringTable(*this).value(getName(uri)));
        return false;
    }
    trigIter->second.kill();
    return true;
}
