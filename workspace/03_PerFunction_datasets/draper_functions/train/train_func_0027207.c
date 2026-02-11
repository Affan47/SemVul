textfield_maxChars(const fn_call& fn)
{
    TextField* text = ensure<IsDisplayObject<TextField> >(fn);

    if (!fn.nargs)
    {
        boost::int32_t maxChars = text->maxChars();
        if (maxChars == 0)
        {
            as_value null;
            null.set_null();
            return null;
        }
        return as_value(maxChars);
    }

    text->maxChars(toInt(fn.arg(0), getVM(fn)));
    return as_value();
}
