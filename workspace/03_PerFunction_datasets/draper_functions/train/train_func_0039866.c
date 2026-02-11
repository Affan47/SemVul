FloatXFORM(_cmsTRANSFORM* p,
                const void* in,
                void* out, cmsUInt32Number Size)
{
    cmsUInt8Number* accum;
    cmsUInt8Number* output;
    cmsFloat32Number fIn[cmsMAXCHANNELS], fOut[cmsMAXCHANNELS];
    cmsFloat32Number OutOfGamut;
    cmsUInt32Number i, j;

    accum  = (cmsUInt8Number*)  in;
    output = (cmsUInt8Number*)  out;

    for (i=0; i < Size; i++) {

        accum = p -> FromInputFloat(p, fIn, accum, Size);


        if (p ->GamutCheck != NULL) {


            cmsPipelineEvalFloat( fIn, &OutOfGamut, p ->GamutCheck);


            if (OutOfGamut > 0.0) {


                for (j=0; j < cmsMAXCHANNELS; j++)
                    fOut[j] = -1.0;

            }
            else {

                cmsPipelineEvalFloat(fIn, fOut, p -> Lut);
            }
        }
        else {


            cmsPipelineEvalFloat(fIn, fOut, p -> Lut);
        }


        output = p -> ToOutputFloat(p, fOut, output, Size);
    }
}
