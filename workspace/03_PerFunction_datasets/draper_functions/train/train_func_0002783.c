read(SWFStream& in)
{
    in.ensureBytes(4 + 4 + 1);

    m_blurX = in.read_ufixed();
    m_blurY = in.read_ufixed();

    m_quality = static_cast<boost::uint8_t> (in.read_uint(5));

    static_cast<void> (in.read_uint(3));

    IF_VERBOSE_PARSE(
        log_parse(_("   BlurFilter: blurX=%f blurY=%f quality=%d"),
        m_blurX, m_blurY, m_quality);
    );

    return true;
}
