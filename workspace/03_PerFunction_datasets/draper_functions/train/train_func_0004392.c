findSyntaxEntry(int verbCode, SyntaxEntry *foundStx) {
    SyntaxEntry *stx;
    for (stx = stxs; !isEndOfArray(stx); stx++)
        if (stx->code == verbCode) {
            foundStx = stx;
            break;
        }
    return(foundStx);
}
