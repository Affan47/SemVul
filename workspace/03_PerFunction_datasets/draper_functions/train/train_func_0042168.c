pixRead(const char  *filename)
{
FILE  *fp;
PIX   *pix;

    PROCNAME("pixRead");

    if (!filename)
        return (PIX *)ERROR_PTR("filename not defined", procName, NULL);

    if ((fp = fopenReadStream(filename)) == NULL)
        return (PIX *)ERROR_PTR("image file not found", procName, NULL);
    if ((pix = pixReadStream(fp, 0)) == NULL) {
        fclose(fp);
        return (PIX *)ERROR_PTR("pix not read", procName, NULL);
    }


    if (pixGetInputFormat(pix) != IFF_GIF)
        fclose(fp);
#ifndef _WIN32
    else
        fclose(fp);
#endif

    return pix;
}
