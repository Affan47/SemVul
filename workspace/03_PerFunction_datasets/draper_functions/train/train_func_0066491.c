findSyntaxTreeForVerb(int verbCode) {
    SyntaxEntry *foundStx = NULL;
    if (isPreBeta2(header->version)) {
	foundStx = findSyntaxEntryForPreBeta2(verbCode, foundStx);
    } else {
	foundStx = findSyntaxEntry(verbCode, foundStx);
    }
    if (foundStx == NULL)

        error(M_WHAT);
    return foundStx;
}
