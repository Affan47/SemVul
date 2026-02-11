Next (Iterator& i) {
    UHashElem* elem = GetElem(i);

    if (elem != nil) {
        int n = Hash(elem->GetKey());
        UList* u = UElem(i);
        u = u->Next();

        if (u == _slot[n]->End()) {
            for (int j = n+1; j < _nslots; ++j) {
                if (_slot[j] != nil) {
                    u = _slot[j]->First();
                    break;
                }
            }
        }
        i.SetValue(u);
    }
}
