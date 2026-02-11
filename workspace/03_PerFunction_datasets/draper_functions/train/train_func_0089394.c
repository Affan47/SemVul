loadFile(const DOMString &fileName)
{
    DOMString buf;

    if (fileName.size() == 0)
        return buf;
    FILE *f = fopen(fileName.c_str(), "rb");
    if (!f)
        {

        return buf;
        }

    while (!feof(f))
        {
        int ch = fgetc(f);
        if (ch<0)
            break;
        buf.push_back((XMLCh)ch);
        }
    fclose(f);

    return buf;
}
