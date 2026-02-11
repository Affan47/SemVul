JPEGVGetField(TIFF* tif, ttag_t tag, va_list ap)
{
        JPEGState* sp = JState(tif);

        assert(sp != NULL);

        switch (tag) {
                case TIFFTAG_JPEGTABLES:
                        *va_arg(ap, uint32*) = sp->jpegtables_length;
                        *va_arg(ap, void**) = sp->jpegtables;
                        break;
                case TIFFTAG_JPEGQUALITY:
                        *va_arg(ap, int*) = sp->jpegquality;
                        break;
                case TIFFTAG_JPEGCOLORMODE:
                        *va_arg(ap, int*) = sp->jpegcolormode;
                        break;
                case TIFFTAG_JPEGTABLESMODE:
                        *va_arg(ap, int*) = sp->jpegtablesmode;
                        break;
                case TIFFTAG_YCBCRSUBSAMPLING:
                        JPEGFixupTestSubsampling( tif );
                        return (*sp->vgetparent)(tif, tag, ap);
                        break;
                case TIFFTAG_FAXRECVPARAMS:
                        *va_arg(ap, uint32*) = sp->recvparams;
                        break;
                case TIFFTAG_FAXSUBADDRESS:
                        *va_arg(ap, char**) = sp->subaddress;
                        break;
                case TIFFTAG_FAXRECVTIME:
                        *va_arg(ap, uint32*) = sp->recvtime;
                        break;
                case TIFFTAG_FAXDCS:
                        *va_arg(ap, char**) = sp->faxdcs;
                        break;
                default:
                        return (*sp->vgetparent)(tif, tag, ap);
        }
        return (1);
}
