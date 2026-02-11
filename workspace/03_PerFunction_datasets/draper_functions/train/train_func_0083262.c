Input()
{

    SetPictureType();
    SetReferenceType();
    SetEntropyCodingFlag();


    if (m_frame_params.GetPictureType() == INTER_PICTURE &&
        m_frame_params.UsingAC() == false)
    {
        DIRAC_THROW_EXCEPTION(
                    ERR_UNSUPPORTED_STREAM_DATA,
                    "VLC codes for entropy coding of coefficient data supported for Intra frames only",
                    SEVERITY_PICTURE_ERROR);
    }


    m_frame_num = ReadUintLit(PP_PICTURE_NUM_SIZE);
    m_frame_params.SetPictureNum(m_frame_num);


    InputReferencePictures();


    m_frame_params.SetRetiredPictureNum(-1);
    if (IsRef())
        InputRetiredPicture();


    ByteAlignInput();

    return true;
}
