read(SWFStream& in)
{
    in.ensureBytes(20 * 4);

    m_matrix.reserve(20);
    for (int i = 0; i < 20; ++i)
    {
        m_matrix.push_back(in.read_long_float());
    }

    IF_VERBOSE_PARSE(
        log_parse(_("   ColorMatrixFilter: "));
        log_parse(_("     %g, %g, %g, %g, %g"),
                  m_matrix[0], m_matrix[1], m_matrix[2],
                  m_matrix[3], m_matrix[4]);
        log_parse(_("     %g, %g, %g, %g, %g"),
                  m_matrix[5], m_matrix[6], m_matrix[7],
                  m_matrix[8], m_matrix[9]);
        log_parse(_("     %g, %g, %g, %g, %g"),
                  m_matrix[10], m_matrix[11], m_matrix[12],
                  m_matrix[13], m_matrix[14]);
        log_parse(_("     %g, %g, %g, %g, %g"),
                    m_matrix[15], m_matrix[16], m_matrix[17],
                  m_matrix[18], m_matrix[19]);
    );

    return true;
}
