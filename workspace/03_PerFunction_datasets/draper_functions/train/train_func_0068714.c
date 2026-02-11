validate(const SyntaxTreeBasePtr& cont, const StringList& metaData,
                                      const string& file, const string& line, bool inParam)
{
    static const string prefix = "cpp:";
    for(StringList::const_iterator p = metaData.begin(); p != metaData.end(); ++p)
    {
        string s = *p;
        if(_history.count(s) == 0)
        {
            if(s.find(prefix) == 0)
            {
                string ss = s.substr(prefix.size());
                if(ss.find("type:string") == 0 || ss.find("type:wstring") == 0)
                {
                    BuiltinPtr builtin = BuiltinPtr::dynamicCast(cont);
                    ModulePtr module = ModulePtr::dynamicCast(cont);
                    ClassDefPtr clss = ClassDefPtr::dynamicCast(cont);
                    StructPtr strct = StructPtr::dynamicCast(cont);
                    ExceptionPtr exception = ExceptionPtr::dynamicCast(cont);
                    if((builtin && builtin->kind() == Builtin::KindString) || module || clss || strct || exception)
                    {
                        continue;
                    }
                }
                if(SequencePtr::dynamicCast(cont))
                {
                    if(ss.find("type:") == 0 || (inParam && (ss == "array" || ss.find("range") == 0)))
                    {
                        continue;
                    }
                }
                cout << file << ":" << line << ": warning: ignoring invalid metadata `" << s << "'" << endl;
            }
            _history.insert(s);
        }
    }
}
