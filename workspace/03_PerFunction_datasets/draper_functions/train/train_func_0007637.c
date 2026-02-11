listReq(int base)
{
    unsigned int dsz=0;
    char* _dataPtr = pack_uint32(LIST_REQ, _data, dsz);
    pack_uint32(base, _dataPtr, dsz);

    (*m_stream) << std::string(_data, dsz) << std::flush;
    setupRecvCmd();

    if (m_timeout.get())
        m_timeout->reset(5000);
    else
    {
        m_timeout.reset( new Timeout(8000) );
        m_timeout->Expired.connect(sigc::mem_fun(this, &Meta::metaTimeout));
    }
}
