update(const unsigned char* in, int len)
{
    if (len < 0)
        len = qstrlen(reinterpret_cast<const char*>(in));

    if (!len)
        return;

    if (m_finalized) {
        kWarning() << "KMD5::update called after state was finalized!";
        return;
    }

    quint32 in_index;
    quint32 buffer_index;
    quint32 buffer_space;
    quint32 in_length = static_cast<quint32>( len );

    buffer_index = static_cast<quint32>((m_count[0] >> 3) & 0x3F);

    if (  (m_count[0] += (in_length << 3))<(in_length << 3) )
        m_count[1]++;

    m_count[1] += (in_length >> 29);
    buffer_space = 64 - buffer_index;

    if (in_length >= buffer_space)
    {
        memcpy (m_buffer + buffer_index, in, buffer_space);
        transform (m_buffer);

        for (in_index = buffer_space; in_index + 63 < in_length;
             in_index += 64)
            transform (reinterpret_cast<const unsigned char*>(in+in_index));

        buffer_index = 0;
    }
    else
        in_index=0;

    memcpy(m_buffer+buffer_index, in+in_index, in_length-in_index);
}
