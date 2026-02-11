pixWriteStream(FILE    *fp,
               PIX     *pix,
               l_int32  format)
{
    PROCNAME("pixWriteStream");

    if (!fp)
        return ERROR_INT("stream not defined", procName, 1);
    if (!pix)
        return ERROR_INT("pix not defined", procName, 1);

    if (format == IFF_DEFAULT)
        format = pixChooseOutputFormat(pix);

    switch(format)
    {
    case IFF_BMP:
        pixWriteStreamBmp(fp, pix);
        break;

    case IFF_JFIF_JPEG:
        return pixWriteStreamJpeg(fp, pix, 75, 0);
        break;

    case IFF_PNG:
        return pixWriteStreamPng(fp, pix, 0.0);
        break;

    case IFF_TIFF:
    case IFF_TIFF_PACKBITS:
    case IFF_TIFF_RLE:
    case IFF_TIFF_G3:
    case IFF_TIFF_G4:
    case IFF_TIFF_LZW:
    case IFF_TIFF_ZIP:
        return pixWriteStreamTiff(fp, pix, format);
        break;

    case IFF_PNM:
        return pixWriteStreamPnm(fp, pix);
        break;

    case IFF_GIF:
        return pixWriteStreamGif(fp, pix);
        break;

    case IFF_PS:
        return pixWriteStreamPS(fp, pix, NULL, 0, DEFAULT_SCALING);
        break;

    default:
        return ERROR_INT("unknown format", procName, 1);
        break;
    }

    return 0;
}
