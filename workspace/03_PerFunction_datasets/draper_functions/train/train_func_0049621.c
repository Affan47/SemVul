indentTo(int indent, FILE *out) {
    for (int i = 0; i < indent; i++) {
        putc(' ',out);
        putc(' ',out);
    }
}
