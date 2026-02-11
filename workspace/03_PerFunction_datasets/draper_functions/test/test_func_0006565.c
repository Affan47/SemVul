trimTrailingChars(String& str, const String& chars)
{
    String::size_type idx = str.find_last_not_of(chars);

    if (idx != String::npos)
    {
        str.resize(idx + 1);
    }
    else
    {
        str.erase();
    }

}

}
