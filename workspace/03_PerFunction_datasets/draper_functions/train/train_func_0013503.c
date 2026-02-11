HandleElse (Token &iBody, int iLine)
{
    if (EnableOutput == 1)
    {
        Error (iLine, "#else without #if");
        return false;
    }


    EnableOutput ^= 1;

    if (iBody.Length)
        Error (iLine, "Warning: Ignoring garbage after #else", &iBody);

    return true;
}
