parse_literal_string_tail(string::const_iterator &start,
                                          const string::const_iterator end)
{
    std::string rval;

    while (start != end && *start != '"') {
        if (*start == '\\') {
            ++start;
            if (start != end) {
                switch (*start) {
                case 'n':
                    rval += '\n';
                    break;
                case 't':
                    rval += '\t';
                    break;
                default:
                    rval += *start;
                    break;
                }
                ++start;
            }
        } else {
            rval += *start;
            ++start;
        }
    }

    if (start == end || *start != '"') {
        m_error = string("Unterminated literal string after " + rval);
        m_hasError = true;
        return string();
    }

    ++start;

    return rval;
}
