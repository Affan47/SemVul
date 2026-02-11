translateForDisplay(bool keepOverlay)
{
    uchar *newbuf;
    int    newspp;
    bool   freeBuffers = !keepOverlay;
    bool   makeChar = (makeImageCharIfFits > 0);
    bool   interpretRGB = (RGBdisplaysRGB > 0);
    bool   minmaxAllSamples = (fitCharOverAllSamples > 0);
    bool   minmaxAllSlices = (fitCharOverAllSlices > 0);

    dbgprintf("Image is [%d]x[%d]x[%d]\n",
              currImgWidth, currImgHeight, currImgThickness);

    if (currBuffp != 0) {
        switch (currPixType) {
        case IM_BINARY:
            convertBINARY(&newspp, &newbuf);
            break;

        case IM_INT1:
        case IM_UINT1:
            convertUINT1(&newspp, &newbuf, freeBuffers, interpretRGB);
            break;


#ifdef HAVE_MEMBER_TEMPLATES
        case IM_INT2:
            convert<short>(&newspp, &newbuf,
                           freeBuffers, makeChar, interpretRGB, minmaxAllSamples, minmaxAllSlices);
            break;

        case IM_UINT2:
            convert<unsigned short>(&newspp, &newbuf,
                                    freeBuffers, makeChar, interpretRGB, minmaxAllSamples, minmaxAllSlices);
            break;

        case IM_INT4:
            convert<int>(&newspp, &newbuf,
                         freeBuffers, makeChar, interpretRGB, minmaxAllSamples, minmaxAllSlices);
            break;

        case IM_UINT4:
            convert<unsigned int>(&newspp, &newbuf,
                                  freeBuffers, makeChar, interpretRGB, minmaxAllSamples, minmaxAllSlices);
            break;

        case IM_FLOAT:
            convert<float>(&newspp, &newbuf,
                           freeBuffers, false, interpretRGB, minmaxAllSamples, minmaxAllSlices);
            break;

        case IM_DOUBLE:
            convert<double>(&newspp, &newbuf,
                            freeBuffers, false, interpretRGB, minmaxAllSamples, minmaxAllSlices);
            break;

#else

        case IM_INT2:
            convertINT2(&newspp, &newbuf);
            break;

        case IM_UINT2:
            convertUINT2(&newspp, &newbuf);
            break;

        case IM_INT4:
            convertINT4(&newspp, &newbuf);
            break;

        case IM_UINT4:
            convertUINT4(&newspp, &newbuf);
            break;

        case IM_DOUBLE:
            convertDOUBLE(&newspp, &newbuf);
            break;
#endif
        default:
            errprintf("imtranslate: format as yet unsupported, type=%s\n",
                      typeName(currPixType));
            freeCurrentBuffers();

            newbuf = new uchar[(long)currImgWidth*(long)currImgHeight];
            newspp = 1;
            break;
        }
        if (newbuf != 0) {
            delete[] imdata;

            imdata = newbuf;


            imspp = newspp;
        }
    } else {
        imspp = currImgNbSamples;
    }
}
