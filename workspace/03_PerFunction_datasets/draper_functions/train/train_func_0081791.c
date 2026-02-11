getNbFrames(const char *fname)
{
    int rv = 0;
    int format = imageFormat(fname);

    switch (format) {
    case IMAGEIO_JPEG:
        rv = jpegnbsubfiles(fname);
        break;

    case IMAGEIO_GIF:
        rv = gifnbsubfiles(fname);
        break;

    case IMAGEIO_TIFF:
        rv = tiffnbsubfiles(fname);
        break;

    case IMAGEIO_ZIMAGE:
        rv = zimagenbsubfiles(fname);
        break;

    case IMAGEIO_SCILIMAGE:
        rv = icsnbsubfiles(fname);
        break;

    case IMAGEIO_METAIMAGE:
        rv = metanbsubfiles(fname);
        break;

    case IMAGEIO_PNM:
        rv = pnmnbsubfiles(fname);
        break;

    case IMAGEIO_PS: {
        mi    p =  psfilemap.find(fname);
        if (p == psfilemap.end()) {

            read(fname);

            if ((p =  psfilemap.find(fname)) != psfilemap.end())
                rv = tiffnbsubfiles((p->second).getfilename().c_str());
            else {
                errprintf("Cannot determine the number of pages in the document\n");
                rv = -50;
            }
        } else {
            rv = tiffnbsubfiles((p->second).getfilename().c_str());
        }
    }
        break;

    case IMAGEIO_MAT5:
        rv = mat5nbsubfiles(fname);
        break;

    case IMAGEIO_PNG:
        rv = pngnbcomp(fname);
        break;

    case IMAGEIO_MAGICK:
        rv = magicknbsubfiles(fname);
        break;

    case IMAGEIO_SOCKET:
        rv = socketnbcomp(fname);
        break;

    case IMAGEIO_RAW:
        rv = rawnbcomp(fname);
        break;

    case IMAGEIO_TOOSMALL:
        errprintf("Input file %s is too small to determine format\n",
                  fname);
        rv = -40;
        break;

    case IMAGEIO_NOTHERE:
        errprintf("No file name given for image input\n");
        rv = -30;
        break;

    case IMAGEIO_UNREADABLE:
        errprintf("Cannot read image %s\n"
                  "%s",
                  fname,
                  strerror(errno));
        rv = -20;
        break;

    case IMAGEIO_UNKNOWN:
        dbgprintf("GetNbFrames: Unrecognized image format: %s\n", fname);
        if (rawImagePanel == 0) {
            rawImagePanel = new rawimage;
            rawimage_panel(*rawImagePanel);

            rawImagePanel->setDefaults();
        }
        rawImagePanel->setFileName(fname);

        rawImagePanel->show();
        rv = -10;
        dbgprintf("Unknown image format\n");
        break;


    default:
        errprintf("Unknown input image error\n");
        rv = -100;
        break;
    }

    dbgprintf("File %s has %d subimages\n",
              fname, rv);
    currImgNbFrames = rv;

    return rv;
}
