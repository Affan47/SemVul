default_normch(int ch)
{
    if (isalnum(ch) || (ch == '_'))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
