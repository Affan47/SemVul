add(const char *c)
{
   if (!c) {
       UString::Rep::null.hash();
       return &UString::Rep::null;
    }

    if (!c[0]) {
        UString::Rep::empty.hash();
        return &UString::Rep::empty;
    }

    return *identifierTable().add<const char *, CStringTranslator>(c).first;
}
