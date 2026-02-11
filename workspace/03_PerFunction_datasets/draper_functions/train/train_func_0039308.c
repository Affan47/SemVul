characterIteratorNext(UCharIterator *iter) {
    if(((CharacterIterator *)(iter->context))->hasNext()) {
        return ((CharacterIterator *)(iter->context))->nextPostInc();
    } else {
        return U_SENTINEL;
    }
}
