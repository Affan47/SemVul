getCodec()
{
    if (m_pVideoCodec)
    {
        return m_pVideoCodec->name;
    }

    return "";
}
