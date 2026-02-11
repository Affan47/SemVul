DeleteElements(TElementList* elems) {
    register TElementList* t;

    for (t = elems->First(); t != elems->End(); t = t->Next()) {
        delete t->GetElem();
    }
}
