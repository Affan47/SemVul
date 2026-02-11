cmsChangeBuffersFormat(cmsHTRANSFORM hTransform,
                                         cmsUInt32Number InputFormat,
                                         cmsUInt32Number OutputFormat)
{

    _cmsTRANSFORM* xform = (_cmsTRANSFORM*) hTransform;
    cmsFormatter16 FromInput, ToOutput;
    cmsUInt32Number BytesPerPixelInput;


    BytesPerPixelInput = T_BYTES(xform ->InputFormat);
    if (!(xform ->dwOriginalFlags & cmsFLAGS_CAN_CHANGE_FORMATTER)) {

        cmsSignalError(xform ->ContextID, cmsERROR_NOT_SUITABLE, "cmsChangeBuffersFormat works only on transforms created originally with at least 16 bits of precision");
        return FALSE;
    }

    FromInput = _cmsGetFormatter(InputFormat,  cmsFormatterInput, CMS_PACK_FLAGS_16BITS).Fmt16;
    ToOutput  = _cmsGetFormatter(OutputFormat, cmsFormatterOutput, CMS_PACK_FLAGS_16BITS).Fmt16;

    if (FromInput == NULL || ToOutput == NULL) {

        cmsSignalError(xform -> ContextID, cmsERROR_UNKNOWN_EXTENSION, "Unsupported raster format");
        return FALSE;
    }

    xform ->InputFormat  = InputFormat;
    xform ->OutputFormat = OutputFormat;
    xform ->FromInput = FromInput;
    xform ->ToOutput  = ToOutput;
    return TRUE;
}
