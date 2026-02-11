getPlain() {
    string concat;

    StringLst.first();
    SPtr<string> s;
    while (s=StringLst.get()) {
        concat.append(*s);
        concat.append(" ");
    }
    return concat;
}
