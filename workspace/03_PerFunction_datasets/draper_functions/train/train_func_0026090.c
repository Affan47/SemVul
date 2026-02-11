Register (void* key, UHashElem* elem) {
    UHashTable::Register(key, elem);
    elem = (elem == nil) ? Find(key) : elem;
    _elems->Append(new UList(elem));
}
