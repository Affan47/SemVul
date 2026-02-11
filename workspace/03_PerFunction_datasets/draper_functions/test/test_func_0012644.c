deleteNextWord() {
    int p = nextWord(curPos, false);
    if (p != curPos) {
        markPos = p;
        return deleteSelection();
    }
    return false;
}
