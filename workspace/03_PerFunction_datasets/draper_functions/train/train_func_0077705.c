AppendVal(Token *t) {
	int reqMem = (tlen + 1) * sizeof(wchar_t);
	if (((char*) heapTop + reqMem) >= (char*) heapEnd) {
		if (reqMem > COCO_HEAP_BLOCK_SIZE) {
			wprintf(L"--- Too long token value\n");
			exit(1);
		}
		CreateHeapBlock();
	}
	t->val = (wchar_t*) heapTop;
	heapTop = (void*) ((char*) heapTop + reqMem);

	wcsncpy(t->val, tval, tlen);
	t->val[tlen] = L'\0';
}
