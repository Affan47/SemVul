Identifier (TextBuffer* tb, int& beg) {
    int i, j;
    const char* text = tb->Text();
    char* string = nil;

    for (i = beg; i < tb->Length(); ++i) {
        if (IsValidChar(text[i])) {
            break;
        }
    }
    for (j = i+1; j < tb->Length(); ++j) {
        char c = text[j];

        if (!IsValidChar(c) && !isdigit(c)) {
            break;
        }
    }
    if (j < tb->Length()) {
        string = strnnew(&text[i], j-i);
        beg = j;
    }
    return string;
}
