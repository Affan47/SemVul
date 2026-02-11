textfield_restrict(const fn_call& fn)
{
    TextField* text = ensure<IsDisplayObject<TextField> >(fn);

    if (!fn.nargs) {

        if (text->isRestrict()) {
            return as_value(text->getRestrict());
        } else {
            as_value null;
            null.set_null();
            return null;
        }
    }

    text->setRestrict(fn.arg(0).to_string());
    return as_value();
}
