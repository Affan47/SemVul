convertToPSEmbed(const char  *filein,
                 const char  *fileout,
                 l_int32      level)
{
const char  nametif[] = "/tmp/junk_convert_ps_embed.tif";
const char  namejpg[] = "/tmp/junk_convert_ps_embed.jpg";
l_int32     d, format;
PIX        *pix, *pixs;

    PROCNAME("convertToPSEmbed");

    if (!filein)
        return ERROR_INT("filein not defined", procName, 1);
    if (!fileout)
        return ERROR_INT("fileout not defined", procName, 1);
    if (level != 1 && level != 2 && level != 3) {
        L_ERROR("invalid level specified; using level 2\n", procName);
        level = 2;
    }

    if (level == 1) {
        pixWritePSEmbed(filein, fileout);
        return 0;
    }


    findFileFormat(filein, &format);
    if (format == IFF_JFIF_JPEG) {
        convertJpegToPSEmbed(filein, fileout);
        return 0;
    } else if (format == IFF_TIFF_G4) {
        convertG4ToPSEmbed(filein, fileout);
        return 0;
    } else if (format == IFF_UNKNOWN) {
        L_ERROR("format of %s not known\n", procName, filein);
        return 1;
    }


    if (level == 3) {
        convertFlateToPSEmbed(filein, fileout);
        return 0;
    }


    if ((pixs = pixRead(filein)) == NULL)
        return ERROR_INT("image not read from file", procName, 1);
    d = pixGetDepth(pixs);
    if ((d == 2 || d == 4) && !pixGetColormap(pixs))
        pix = pixConvertTo8(pixs, 0);
    else if (d == 16)
        pix = pixConvert16To8(pixs, 1);
    else
        pix = pixRemoveColormap(pixs, REMOVE_CMAP_BASED_ON_SRC);

    d = pixGetDepth(pix);
    if (d == 1) {
        pixWrite(nametif, pix, IFF_TIFF_G4);
        convertG4ToPSEmbed(nametif, fileout);
    } else {
        pixWrite(namejpg, pix, IFF_JFIF_JPEG);
        convertJpegToPSEmbed(namejpg, fileout);
    }

    pixDestroy(&pix);
    pixDestroy(&pixs);
    return 0;
}
