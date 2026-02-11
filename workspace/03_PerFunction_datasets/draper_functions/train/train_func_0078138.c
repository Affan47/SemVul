convertEntityInText(const String& text)
{
    String res;
    res.reserve(text.size()*2);
    const String::const_iterator iterEnd = text.end();
    for (String::const_iterator iter = text.begin(); iter != iterEnd ; ++iter)
    {
        switch(*iter)
        {
            case '<':
                res +=(utf8*)"&lt;";
                break;

            case '>':
                res +=(utf8*)"&gt;";
                break;

            case '&':
                res += (utf8*)"&amp;";
                break;

            case '\'':
                res += (utf8*)"&apos;";
                break;

            case '"':
                res += (utf8*)"&quot;";
                break;

            default:
                res += *iter;
        }
    }
    return res;
}
