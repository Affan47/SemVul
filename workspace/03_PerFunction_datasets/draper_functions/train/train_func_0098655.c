pixWrite(const char  *filename,
         PIX         *pix,
         l_int32      format)
{
FILE  *fp;

    PROCNAME("pixWrite");

    if (!pix)
        return ERROR_INT("pix not defined", procName, 1);
    if (!filename)
        return ERROR_INT("filename not defined", procName, 1);
    if (format == IFF_JP2)
        return ERROR_INT("jp2 not supported", procName, 1);

#if  WRITE_AS_NAMED

    if ((fp = fopen(filename, "wb+")) == NULL)
        return ERROR_INT("stream not opened", procName, 1);

#else

    {l_int32  extlen;
     char    *extension, *filebuf;
        splitPathAtExtension(filename, NULL, &extension);
        extlen = strlen(extension);
        FREE(extension);
        if (extlen == 0) {
            if (format == IFF_DEFAULT || format == IFF_UNKNOWN)
                format = pixChooseOutputFormat(pix);

            filebuf = (char *)CALLOC(strlen(filename) + 10, sizeof(char));
            if (!filebuf)
                return ERROR_INT("filebuf not made", procName, 1);
            strncpy(filebuf, filename, strlen(filename));
            strcat(filebuf, ".");
            strcat(filebuf, ImageFileFormatExtensions[format]);
        }
        else
            filebuf = (char *)filename;

        fp = fopen(filebuf, "wb+");
        if (filebuf != filename)
            FREE(filebuf);
        if (fp == NULL)
            return ERROR_INT("stream not opened", procName, 1);
    }

#endif

    if (pixWriteStream(fp, pix, format)) {
        fclose(fp);
        return ERROR_INT("pix not written to stream", procName, 1);
    }


    if (format != IFF_GIF)
        fclose(fp);
#ifndef _WIN32
    else
        fclose(fp);
#endif

    return 0;
}
