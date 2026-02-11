writeNewline() {
    for (uint32 i = 0; i < newline.size(); ++i) {
        indentAppend(newline[i]);
    }
}
