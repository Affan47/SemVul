CalcParseCode() const
{
    unsigned char code = 0;

    int num_refs = m_frame_params.Refs().size();

    if(m_frame_params.GetPictureType()==INTER_PICTURE)
    {

        if(num_refs == 1)
            SetBit(code, CODE_ONE_REF_BIT);
        if(num_refs > 1)
            SetBit(code, CODE_TWO_REF_BIT);
    }

    if(m_frame_params.GetReferenceType()==REFERENCE_PICTURE)
        SetBit(code, CODE_REF_PICTURE_BIT);


    SetBit(code, CODE_PUTYPE_1_BIT);


    if (!m_frame_params.UsingAC())
    {
        SetBit(code, CODE_VLC_ENTROPY_CODING_BIT);
    }
    return code;


}
