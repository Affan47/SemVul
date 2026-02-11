SetDefaultEncoderParameters(EncoderParams& encparams)
{
    encparams.SetLossless(false);
    encparams.SetQf(5.5f);
    encparams.GetPicPredParams().SetMVPrecision(MV_PRECISION_HALF_PIXEL);
    encparams.SetUsingAC(true);

    switch (encparams.GetVideoFormat())
    {
    case VIDEO_FORMAT_4SIF525:
    case VIDEO_FORMAT_4CIF:
    case VIDEO_FORMAT_SD_480I60:
    case VIDEO_FORMAT_SD_576I50:
        encparams.SetL1Sep(3);
        encparams.SetNumL1(7);
        encparams.SetCPD(32.0f);
        break;

    case VIDEO_FORMAT_HD_720P60:
    case VIDEO_FORMAT_HD_720P50:
        encparams.SetL1Sep(3);
        encparams.SetNumL1(15);
        encparams.SetCPD(20.0f);
        break;

    case VIDEO_FORMAT_HD_1080I60:
    case VIDEO_FORMAT_HD_1080I50:
    case VIDEO_FORMAT_HD_1080P60:
    case VIDEO_FORMAT_HD_1080P50:
        encparams.SetL1Sep(3);
        encparams.SetNumL1(7);
        encparams.SetCPD(32.0f);
        break;
    case VIDEO_FORMAT_UHDTV_4K60:
    case VIDEO_FORMAT_UHDTV_4K50:
    case VIDEO_FORMAT_UHDTV_8K60:
    case VIDEO_FORMAT_UHDTV_8K50:
        encparams.SetL1Sep(6);
        encparams.SetNumL1(7);
        encparams.SetCPD(48.0f);
        break;
    case VIDEO_FORMAT_CIF:
    default:
        encparams.SetL1Sep(3);
        encparams.SetNumL1(19);
        encparams.SetCPD(20.0f);
        break;
    }

}
