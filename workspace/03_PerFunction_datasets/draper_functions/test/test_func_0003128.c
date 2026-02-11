executeTriggers(Property* prop, const ObjectURI& uri,
                           const as_value& val)
{


    TriggerContainer::iterator trigIter;


    if (!_trigs.get() || (trigIter = _trigs->find(uri)) == _trigs->end()) {
        if (prop) {
            prop->setValue(*this, val);
            prop->clearVisible(getSWFVersion(*this));
        }
        return;
    }

    Trigger& trig = trigIter->second;

    if (trig.dead()) {
        _trigs->erase(trigIter);
        return;
    }


    const as_value& curVal = prop ? prop->getCache() : as_value();
    const as_value& newVal = trig.call(curVal, val, *this);


    EraseIf(*_trigs, boost::bind(boost::mem_fn(&Trigger::dead),
             boost::bind(&TriggerContainer::value_type::second, _1)));


    prop = findUpdatableProperty(uri);
    if (!prop) return;

    prop->setValue(*this, newVal);
    prop->clearVisible(getSWFVersion(*this));

}
