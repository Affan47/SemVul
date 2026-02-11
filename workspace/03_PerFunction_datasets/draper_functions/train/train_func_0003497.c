parseCDATA(int p0, CDATASectionPtr cdata)
{

    int p = p0;

    if (!match(p, "<![CDATA["))
        return p0;

    colNr += 9;
    p     += 9;

    DOMString buf;

    while (p<len)
        {
        if (match(p, "]]>"))
            {
            p     +=3;
            colNr += 3;
            break;
            }
        int ch = get(p++);
        buf.push_back((XMLCh)ch);
        }


    cdata->setNodeValue(buf);

    return p;
}
