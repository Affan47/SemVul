writeConstantValue(const TypePtr& type, const string& value)
{
    Slice::BuiltinPtr b = Slice::BuiltinPtr::dynamicCast(type);
    Slice::EnumPtr en = Slice::EnumPtr::dynamicCast(type);
    if(b)
    {
        switch(b->kind())
        {
        case Slice::Builtin::KindBool:
        {
            _out << (value == "true" ? "True" : "False");
            break;
        }
        case Slice::Builtin::KindByte:
        case Slice::Builtin::KindShort:
        case Slice::Builtin::KindInt:
        case Slice::Builtin::KindFloat:
        case Slice::Builtin::KindDouble:
        case Slice::Builtin::KindLong:
        {
            _out << value;
            break;
        }
        case Slice::Builtin::KindString:
        {


            static const string basicSourceChars = "abcdefghijklmnopqrstuvwxyz"
                                                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                                   "0123456789"
                                                   "_{}[]#()<>%:;.?*+-/^&|~!=, '";
            static const set<char> charSet(basicSourceChars.begin(), basicSourceChars.end());

            _out << "\"";

            for(string::const_iterator c = value.begin(); c != value.end(); ++c)
            {
                switch(*c)
                {
                case '"':
                {
                    _out << "\\\"";
                    break;
                }
                case '\\':
                {
                    _out << "\\\\";
                    break;
                }
                case '\r':
                {
                    _out << "\\r";
                    break;
                }
                case '\n':
                {
                    _out << "\\n";
                    break;
                }
                case '\t':
                {
                    _out << "\\t";
                    break;
                }
                case '\b':
                {
                    _out << "\\b";
                    break;
                }
                case '\f':
                {
                    _out << "\\f";
                    break;
                }
                default:
                {
                    if(charSet.find(*c) == charSet.end())
                    {
                        unsigned char uc = *c;
                        stringstream s;
                        s << "\\";
                        s.flags(ios_base::oct);
                        s.width(3);
                        s.fill('0');
                        s << static_cast<unsigned>(uc);
                        _out << s.str();
                    }
                    else
                    {
                        _out << *c;
                    }
                    break;
                }
                }
            }

            _out << "\"";
            break;
        }
        case Slice::Builtin::KindObject:
        case Slice::Builtin::KindObjectProxy:
        case Slice::Builtin::KindLocalObject:
            assert(false);
        }
    }
    else if(en)
    {
        string enumName = getSymbol(en);
        string::size_type colon = value.rfind(':');
        string enumerator;
        if(colon != string::npos)
        {
            enumerator = fixIdent(value.substr(colon + 1));
        }
        else
        {
            enumerator = fixIdent(value);
        }
        _out << enumName << '.' << enumerator;
    }
    else
    {
        assert(false);
    }
}
