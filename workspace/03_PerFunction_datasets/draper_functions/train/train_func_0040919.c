parseDocTypeDecl(xml_iterator& it, const xml_iterator end)
{

    xml_iterator ourend;
    xml_iterator current = it;

    std::string::size_type count = 1;


    while (count) {


        ourend = std::find(current, end, '>');
        if (ourend == end) {
            _status = XML_UNTERMINATED_DOCTYPE_DECL;
            return;
        }
        --count;


        count += std::count(current, ourend, '<');
        current = ourend;
        ++current;
    }

    const std::string content(it, ourend);
    std::ostringstream os;
    os << '<' << content << '>';
    _docTypeDecl = os.str();
    it = ourend + 1;
}
