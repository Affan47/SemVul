operator[]( int index ) const {
	if (0 <= index && index < Count) {
		SortedEntry* pSortedEntry = Data;
		for (int i=0; i<index; i++) {
			pSortedEntry = pSortedEntry->next;
		}
		return pSortedEntry;
	} else {
		return NULL;
	}
}

}
