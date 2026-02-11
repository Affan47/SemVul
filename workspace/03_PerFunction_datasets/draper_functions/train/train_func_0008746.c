unescattr(string s)
{
    Regex octal("\\\\[0-3][0-7][0-7]");
    Regex esc_quote("\\\\\"");
    Regex esc_esc("\\\\\\\\");
    const string ESC = "\\";
    const string QUOTE = "\"";
    int matchlen;
    unsigned int index;

    DBG(cerr << "0XX" << s << "XXX" << endl);

    index = esc_esc.search(s.c_str(), s.length(), matchlen, 0);
    while (index < s.length()) {
        DBG(cerr << "1aXX" << s << "XXX index: " << index << endl);
        s.replace(index, 2, ESC);
        DBG(cerr << "1bXX" << s << "XXX index: " << index << endl);
        index = esc_esc.search(s.c_str(), s.length(), matchlen, 0);
    }


    index = esc_quote.search(s.c_str(), s.length(), matchlen, 0);
    while (index < s.length()) {
        s.replace(index, 2, QUOTE);
        DBG(cerr << "2XX" << s << "XXX index: " << index << endl);
        index = esc_quote.search(s.c_str(), s.length(), matchlen, 0);
    }


    index = octal.search(s.c_str(), s.length(), matchlen, 0);
    while (index < s.length()) {
        s.replace(index, 4, unoctstring(s.substr(index + 1, 3)));
        DBG(cerr << "3XX" << s << "XXX index: " << index << endl);
        index = octal.search(s.c_str(), s.length(), matchlen, 0);
    }

    DBG(cerr << "4XX" << s << "XXX" << endl);
    return s;
}
