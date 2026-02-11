codeAudioType(AudioType* t)
{
    SimpleType 	*st;
    TableType   *tt;
    TupletType	*nt;

    Tree        r;

    if ((r=t->getCode())) return r;

    if ((st = isSimpleType(t))) {
        r = codeSimpleType(st);
    } else if ((tt = isTableType(t))) {
        r = codeTableType(tt);
    } else if ((nt = isTupletType(t))) {
        r = codeTupletType(nt);
    } else {
        cerr << "ERROR in codeAudioType() : invalide pointer " << t << endl;
        exit(1);
    }

    r->setType(t);
    return r;

}
