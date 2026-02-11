mangle(bool isv)
{
    Dsymbol *parentsave = parent;


    if (ident == Id::Exception)
    {   if (parent->ident == Id::object)
            parent = NULL;
    }
    else if (ident == Id::TypeInfo   ||

        ident == Id::TypeInfo_Struct   ||
        ident == Id::TypeInfo_Class    ||
        ident == Id::TypeInfo_Typedef  ||
        ident == Id::TypeInfo_Tuple ||
        this == object     ||
        this == Type::typeinfoclass  ||
        this == Module::moduleinfo ||
        memcmp(ident->toChars(), "TypeInfo_", 9) == 0
       )
        parent = NULL;

    const char *id = AggregateDeclaration::mangle(isv);
    parent = parentsave;
    return id;
}
