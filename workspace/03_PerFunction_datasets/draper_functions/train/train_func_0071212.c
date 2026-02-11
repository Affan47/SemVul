GetAtomTotalSize(JSContext *cx, JSAtom *atom)
{
    size_t nbytes;

    nbytes = sizeof(JSAtom *) + sizeof(JSDHashEntryStub);
    if (ATOM_IS_STRING(atom)) {
        nbytes += sizeof(JSString);
        nbytes += (ATOM_TO_STRING(atom)->flatLength() + 1) * sizeof(jschar);
    } else if (ATOM_IS_DOUBLE(atom)) {
        nbytes += sizeof(jsdouble);
    }
    return nbytes;
}
