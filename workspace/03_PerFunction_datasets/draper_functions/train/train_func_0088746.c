StartStreaming(const char* privname)
{
    if (m_pVideodecoder)
        return 0;

    if (!(m_pVideodecoder = CreateDecoderVideo(*(const BITMAPINFOHEADER*)m_pFormat,
					       24, flip, privname)))
	return -1;

    m_pVideodecoder->Start();

    AVM_WRITE("video reader", 2, "ReadStreamV::StartStreaming()  %f\n", m_dLastTime);
    return 0;
}
