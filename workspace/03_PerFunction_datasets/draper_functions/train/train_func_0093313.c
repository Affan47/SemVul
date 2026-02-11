decode(string data)
{
    string::size_type  i;
    char               c;
    char               c1;
    string::size_type  len = data.length();
    string             ret;
    for (i = 0; i < len; ++i)
    {
        c = (char) cvt.find(data[i]);
        ++i;
        c1 = (char) cvt.find(data[i]);
        c = (c << 2) | ((c1 >> 4) & 0x3);
        ret.append(1, c);
        if (++i < len)
        {
            c = data[i];
            if (fillchar == c)
                break;
            c = (char) cvt.find(c);
            c1 = ((c1 << 4) & 0xf0) | ((c >> 2) & 0xf);
            ret.append(1, c1);
        }
        if (++i < len)
        {
            c1 = data[i];
            if (fillchar == c1)
                break;
            c1 = (char) cvt.find(c1);
            c = ((c << 6) & 0xc0) | c1;
            ret.append(1, c);
        }
    }
    return(ret);
}
