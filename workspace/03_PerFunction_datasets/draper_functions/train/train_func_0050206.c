contentEditable() const
{
    document()->updateRendering();

    if (!renderer())
        return "false";

    switch (renderer()->style()->userInput()) {
        case UI_ENABLED:
            return "true";
        case UI_DISABLED:
        case UI_NONE:
            return "false";
        default: ;
    }
    return "inherit";
}
