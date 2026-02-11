registerTextVariable()
{


#ifdef DEBUG_DYNTEXT_VARIABLES
    log_debug("registerTextVariable() called");
#endif

    if (_text_variable_registered) {
        return;
    }

    if (_variable_name.empty()) {
        _text_variable_registered = true;
        return;
    }

    VariableRef varRef = parseTextVariableRef(_variable_name);
    as_object* target = varRef.first;
    if (!target) {
        log_debug("VariableName associated to text field (%s) refer to "
                    "an unknown target. It is possible that the DisplayObject "
                    "will be instantiated later in the SWF stream. "
                    "Gnash will try to register again on next access.",
                _variable_name);
        return;
    }

    const ObjectURI& key = varRef.second;
    as_object* obj = getObject(this);
    const int version = getSWFVersion(*obj);


    as_value val;
    if (target->get_member(key, &val)) {

        setTextValue(utf8::decodeCanonicalString(val.to_string(), version));
    }
    else if (_textDefined) {
        as_value newVal = as_value(utf8::encodeCanonicalString(_text, version));
        target->set_member(key, newVal);
    }

    MovieClip* sprite = get<MovieClip>(target);

    if (sprite) {


        sprite->set_textfield_variable(key, this);

    }
    _text_variable_registered = true;
}
