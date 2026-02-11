strncatUsageError(const Token *tok)
{
    if (_settings && !_settings->isEnabled("style"))
        return;

    reportError(tok, Severity::warning, "strncatUsage",
                "Dangerous usage of strncat - 3rd parameter is the maximum number of characters to append.\n"
                "strncat appends at max its 3rd parameter's amount of characters. The safe way to use "
                "strncat is to calculate remaining space in the buffer and use it as 3rd parameter.");
}
