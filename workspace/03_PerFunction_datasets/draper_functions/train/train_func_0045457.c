read_text(int len, int *count = NULL, int *sum = NULL)
    {
        char c;
        QString res = "";
        for (int i = 0; i < len; ++i) {
            if (file.read(&c, 1) != 1)
                throw TruncatedRead();
            if (sum)
                *sum += (0xff & c);
            if (count)
                *count += 1;

            res += c;
        }
        return res;
    }
