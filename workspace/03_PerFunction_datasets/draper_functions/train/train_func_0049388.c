readPrevLine(std::string& line, const byte* data, size_t startPos, size_t size)
    {
        line.clear();
        size_t pos = startPos;
        if (pos > size) return pos;

        if (pos <= 0) return pos;
        if (data[pos - 1] == '\r' || data[pos - 1] == '\n') {
            pos--;
            if (pos <= 0) return pos;
            if (data[pos - 1] == '\r' && data[pos] == '\n') {
                pos--;
                if (pos <= 0) return pos;
            }
        }

        while (pos >= 1 && data[pos - 1] != '\r' && data[pos - 1] != '\n') {
            pos--;
            line += data[pos];
        }
        std::reverse(line.begin(), line.end());
        return pos;
    }
