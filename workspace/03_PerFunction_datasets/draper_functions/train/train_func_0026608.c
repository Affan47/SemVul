firstPostInc() {
    pos = begin;
    if(pos < end) {
        return text[pos++];
    } else {
        return DONE;
    }
}
