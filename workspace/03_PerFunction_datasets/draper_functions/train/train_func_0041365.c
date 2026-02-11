Input()
{

    InputParseParams();


    SetByteParams(m_parseparams_byteio);
    VideoFormat vf = IntToVideoFormat(ReadUint());
    if(vf==VIDEO_FORMAT_UNDEFINED)
         DIRAC_THROW_EXCEPTION(
                    ERR_INVALID_VIDEO_FORMAT,
                    "Dirac does not recognise the specified video-format",
                    SEVERITY_ACCESSUNIT_ERROR);

    SourceParams src_params(vf, true);
    m_src_params = src_params;

    InputSourceParams();

    CodecParams codec_params(vf);
    m_codec_params = codec_params;

    InputCodingParams();

    return true;
}
