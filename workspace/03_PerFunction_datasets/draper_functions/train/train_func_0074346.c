visitConst(const ConstPtr& p)
{
    H << sp;
    H << nl << "const " << typeToString(p->type(), _useWstring, p->typeMetaData()) << " " << fixKwd(p->name())
      << " = ";

    BuiltinPtr bp = BuiltinPtr::dynamicCast(p->type());
    if(bp && bp->kind() == Builtin::KindString)
    {


        static const string basicSourceChars = "abcdefghijklmnopqrstuvwxyz"
                                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                               "0123456789"
                                               "_{}[]#()<>%:;.?*+-/^&|~!=,\\\"' ";
        static const set<char> charSet(basicSourceChars.begin(), basicSourceChars.end());

        ostringstream initString;
        initString << "\"";

        const string val = p->value();
        for(string::const_iterator c = val.begin(); c != val.end(); ++c)
        {
            if(charSet.find(*c) == charSet.end())
            {
                unsigned char uc = *c;
                ostringstream s;
                s << "\\";
                s.flags(ios_base::oct);
                s.width(3);
                s.fill('0');
                s << static_cast<unsigned>(uc);
                initString << s.str();
            }
            else
            {
                initString << *c;
            }
        }
        initString << "\"";

        bool isWstring = _useWstring || findMetaData(p->typeMetaData(), true) == "wstring";
        if(isWstring)
        {
            H.zeroIndent();
            H << "#ifdef ICEE_HAS_WSTRING";
            H.restoreIndent();
            H << 'L' << initString.str();;
            H.zeroIndent();
            H << "#else";
            H.restoreIndent();
        }
        H << initString.str();
        if(isWstring)
        {
            H.zeroIndent();
            H << "#endif";
            H.restoreIndent();
        }
    }
    else if(bp && bp->kind() == Builtin::KindLong)
    {
        H << "ICE_INT64(" << p->value() << ")";
    }
    else
    {
        EnumPtr ep = EnumPtr::dynamicCast(p->type());
        if(ep)
        {
            H << fixKwd(p->value());
        }
        else
        {
            H << p->value();
        }
    }

    H << ';';
}
