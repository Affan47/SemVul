UnrollLabFloatToFloat(_cmsTRANSFORM* info,
                                      cmsFloat32Number wIn[],
                                      cmsUInt8Number* accum,
                                      cmsUInt32Number Stride)
{
    cmsFloat32Number* Pt = (cmsFloat32Number*) accum;

    if (T_PLANAR(info -> InputFormat)) {

        wIn[0] = (cmsFloat32Number) (Pt[0] / 100.0);
        wIn[1] = (cmsFloat32Number) ((Pt[Stride] + 128) / 255.0);
        wIn[2] = (cmsFloat32Number) ((Pt[Stride*2] + 128) / 255.0);

        return accum + sizeof(cmsFloat32Number);
    }
    else {

        wIn[0] = (cmsFloat32Number) (Pt[0] / 100.0);
        wIn[1] = (cmsFloat32Number) ((Pt[1] + 128) / 255.0);
        wIn[2] = (cmsFloat32Number) ((Pt[2] + 128) / 255.0);

        accum += sizeof(cmsFloat32Number)*(3 + T_EXTRA(info ->InputFormat));
        return accum;
    }
}
