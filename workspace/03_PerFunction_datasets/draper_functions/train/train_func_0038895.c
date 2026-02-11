IsDoxygenChar (const int ch)
{
    return isalpha(ch) || (ch == '$') || (ch == '[') || (ch == ']') || (ch == '{') || (ch == '}');
}
