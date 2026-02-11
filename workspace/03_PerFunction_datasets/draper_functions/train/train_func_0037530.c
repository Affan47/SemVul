readLine(bool block)
{
    d->m_Inbuf = readAll(block);

    int pos;
    QByteArray ret;
    if (!d->m_Inbuf.isEmpty())
    {
        pos = d->m_Inbuf.indexOf('\n');
        if (pos == -1)
        {

            ret = d->m_Inbuf;
            d->m_Inbuf.resize(0);
        } else
        {
            ret = d->m_Inbuf.left(pos);
            d->m_Inbuf.remove(0, pos+1);
        }
    }

    return ret;
}
