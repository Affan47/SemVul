OutputChromaSamplingFormat()
{

    bool not_default =  m_src_params.CFormat()!=m_default_src_params.CFormat();

    WriteBit(not_default);

    if(!not_default)
        return;


    WriteUint(static_cast<int>(m_src_params.CFormat()));
}
