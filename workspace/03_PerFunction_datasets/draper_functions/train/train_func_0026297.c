getLine_intern(string& line)
{
    if (offset==read) return false;

    size_t lineEnd;
    {
        size_t  rest   = read-offset;
        char   *eolPos = (char*)memchr(buf+offset, eol[0], rest);

        if (!eolPos) {
            eolPos = (char*)memchr(buf+offset, eol[1], rest);
            if (!eolPos) {
                lineEnd = read;
            }
            else {
                swap(eol[0], eol[1]);
                lineEnd = eolPos-buf;
            }
        }
        else {
            lineEnd = eolPos-buf;
            if (lineEnd>0 && buf[lineEnd-1] == eol[1]) {
                swap(eol[0], eol[1]);
                lineEnd--;
            }
        }
    }

    if (lineEnd<read) {
        line    = string(buf+offset, lineEnd-offset);
        char lf = buf[lineEnd];

        offset = lineEnd+1;
        if (offset == read) fillBuffer();

        if (offset<read) {
            char nextChar = buf[offset];
            if (is_EOL(nextChar) && nextChar != lf) offset++;
            if (offset == read) fillBuffer();
        }
    }
    else {
        line = string(buf+offset, read-offset);
        fillBuffer();
        string rest;
        if (getLine_intern(rest)) line = line+rest;
    }

    return true;
}
