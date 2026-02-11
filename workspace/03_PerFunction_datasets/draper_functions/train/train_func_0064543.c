_cmsReadOutputLUT(cmsHPROFILE hProfile, int Intent)
{
    cmsTagTypeSignature OriginalType;
    cmsTagSignature tag16    = PCS2Device16[Intent];
    cmsTagSignature tagFloat = PCS2DeviceFloat[Intent];
    cmsContext ContextID     = cmsGetProfileContextID(hProfile);

    if (cmsIsTag(hProfile, tagFloat)) {


        return cmsPipelineDup((cmsPipeline*) cmsReadTag(hProfile, tagFloat));
    }


    if (!cmsIsTag(hProfile, tag16)) {
        tag16 = PCS2Device16[0];
    }

    if (cmsIsTag(hProfile, tag16)) {


        cmsPipeline* Lut = (cmsPipeline*) cmsReadTag(hProfile, tag16);
        if (Lut == NULL) return NULL;


        OriginalType =  _cmsGetTagTrueType(hProfile, tag16);


        Lut = cmsPipelineDup(Lut);
        if (Lut == NULL) return NULL;


        if (cmsGetPCS(hProfile) == cmsSigLabData)
                             ChangeInterpolationToTrilinear(Lut);


        if (OriginalType != cmsSigLut16Type || cmsGetPCS(hProfile) != cmsSigLabData)
            return Lut;


        cmsPipelineInsertStage(Lut, cmsAT_BEGIN, _cmsStageAllocLabV4ToV2(ContextID));
        return Lut;
    }


     if (cmsGetColorSpace(hProfile) == cmsSigGrayData) {


              return BuildGrayOutputPipeline(hProfile);
    }


    return BuildRGBOutputMatrixShaper(hProfile);
}
