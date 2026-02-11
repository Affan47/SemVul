FindColorizer(const char *AName) {
    EColorize *p = Colorizers;

    while (p) {
        if (p->Name == AName)
            return p;
        p = p->Next;
    }
    return 0;
}
