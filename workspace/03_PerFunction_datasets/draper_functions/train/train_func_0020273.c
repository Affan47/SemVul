SetCodeBlockMode (unsigned int cb_mode)
{
    if (cb_mode >= QUANT_UNDEF)
    {
        std::ostringstream errstr;
        errstr << "Code Block mode " << cb_mode << " out of supported range [0-" << QUANT_MULTIPLE  << "]";
        DIRAC_THROW_EXCEPTION(
            ERR_UNSUPPORTED_STREAM_DATA,
            errstr.str(),
            SEVERITY_PICTURE_ERROR);
    }

    m_cb_mode = static_cast<CodeBlockMode>(cb_mode);
}
