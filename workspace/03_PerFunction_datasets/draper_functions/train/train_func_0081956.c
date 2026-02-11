trim_trailing_ws (tstring & str)
{
    tstring::iterator it = str.end();
    for (; it != str.begin(); --it)
     {
        if (! is_space (*(it - 1)))
             break;
     }
    str.resize(it - str.begin());
}
