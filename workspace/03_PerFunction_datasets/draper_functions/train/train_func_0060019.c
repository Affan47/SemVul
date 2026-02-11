skipSpaces(void)


{
    char c;

    while ((c = getTexChar()) && c == ' ') {
    }
    ungetTexChar(c);
}
