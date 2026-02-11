Get_Line (
    const char* s, int size, int begin, int& end, int& lineSize, int& nextBegin
) {
    int i = begin;

    while (i < size) {
        if (s[i] == '\n') {
            break;
        } else {
            ++i;
        }
    }
    end = i - 1;
    nextBegin = i + 1;
    lineSize = i - begin;
}
