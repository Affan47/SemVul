object_toString(const fn_call& fn)
{
    as_object* obj = ensure<ValidThis>(fn);
    return as_value(obj->stringValue());
}
