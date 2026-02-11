dump_string(unsigned int indent, const std::string& str)
{
    bool newline_pending = false;
    unsigned int i, j;
    for (i = 0; i < str.size(); i++) {
        if (newline_pending) {
            putchar('\n');
            if ('\n' != str[i]) {
                for (j = 0; j < indent; j++) {
                    putchar(' ');
                }
            }
            newline_pending = false;
        }
        if ('\n' == str[i]) {
            newline_pending = true;
        } else {
            putchar(str[i]);
        }
    }
    if (newline_pending) {
        putchar('\n');
    }
}
