getBraceParam0(int raw_flag)


{
    char s[2], *text;

    s[0] = getNonSpace();
    if (s[0] == '\n')
        s[0] = getNonSpace();

    PushTrackLineNumber(FALSE);

    if (s[0] == '\\') {
        ungetTexChar(s[0]);
        text = getSimpleCommand();

    } else if (s[0] == '{')
        text = getDelimitedText('{', '}', raw_flag);

    else {
        s[1] = '\0';
        text = strdup(s);
    }

    PopTrackLineNumber();
    diagnostics(6, "Leaving getBraceParam {%s}", text);
    return text;
}
