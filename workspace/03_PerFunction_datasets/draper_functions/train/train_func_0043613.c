visitDictionary(const DictionaryPtr& p)
{


    string name = fixIdent(p->name(), IdentToUpper);
    string scoped = p->scoped();
    _out << sp << nl << "if not defined?(" << getAbsolute(p, IdentToUpper, "T_") << ')';
    _out.inc();
    _out << nl << "T_" << name << " = ::Ice::__defineDictionary('" << scoped << "', ";
    writeType(p->keyType());
    _out << ", ";
    writeType(p->valueType());
    _out << ")";
    _out.dec();
    _out << nl << "end";
}
