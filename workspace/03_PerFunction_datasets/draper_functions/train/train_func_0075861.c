escapeRememberChars(const string& str) {
    if (str.empty())
        return str;

    string escaped_str;
    escaped_str.reserve(str.capacity());

    string::const_iterator i;
    for (i = str.begin(); i != str.end(); ++i) {
        switch (*i) {
            case '(': case ')': case '[': case ']':
                escaped_str += '\\';
            default:
                escaped_str += *i;
        }
    }

    return escaped_str;
}
