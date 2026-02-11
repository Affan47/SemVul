setText(DOMStringImpl *text, bool force)
{
    if (!force && str == text)
        return;

    setTextInternal(text);
}
