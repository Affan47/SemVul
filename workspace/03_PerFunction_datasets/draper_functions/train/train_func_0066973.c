SetColorSpace(fourcc_t csp, bool test_only)
{
    if (!m_pVideostream || !m_pVideostream->GetVideoDecoder())
	return -1;


    if (!test_only)
	return m_pVideostream->GetVideoDecoder()->SetDestFmt(0, csp);

    IVideoDecoder::CAPS cap;
    switch (csp)
    {
    case fccYUY2:
	cap = IVideoDecoder::CAP_YUY2;
        break;
    case fccI420:
	cap = IVideoDecoder::CAP_I420;
	break;
    case fccYV12:
	cap = IVideoDecoder::CAP_YV12;
        break;
    case fccIYUV:
	cap = IVideoDecoder::CAP_IYUV;
        break;
    case fccUYVY:
	cap = IVideoDecoder::CAP_UYVY;
        break;
    case fccYVYU:
	cap = IVideoDecoder::CAP_YVYU;
	break;
    default:
	cap = IVideoDecoder::CAP_NONE;
    }

    return !(m_pVideostream->GetVideoDecoder()->GetCapabilities() & cap);
}
