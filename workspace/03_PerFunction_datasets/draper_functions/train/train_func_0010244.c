CheckLevel()
{
    std::ostringstream errstr;
    ParseParams def_parse_params;


    if (def_parse_params.Level() == 0)
        return;


    if (def_parse_params.Level() != 0)
    {
        if ((m_parse_params.Profile() <= 2 && m_parse_params.Level() != 1) ||
            (m_parse_params.Profile() ==8 && m_parse_params.Level() != 128))
        {
            errstr << "Cannot handle Level " << m_parse_params.Level()
                   << " for bitstream version " << m_parse_params.MajorVersion()
                   << ". " << m_parse_params.MinorVersion()
                   << " Profile " << m_parse_params.Profile()
                   << ". Supported levels are 1 for Profiles 0, 1, 2 "
                   << "  and 128 for Profile 8";
            errstr << ". May not be able to decode bitstream correctly" << std::endl;
        }
    }

    if (errstr.str().size())
    {
        DiracException err(
            ERR_UNSUPPORTED_STREAM_DATA,
            errstr.str(),
            SEVERITY_PICTURE_ERROR);
        DIRAC_LOG_EXCEPTION(err);
    }
    return;
}
