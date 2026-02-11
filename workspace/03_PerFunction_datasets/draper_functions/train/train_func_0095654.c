UnrollXYZFloatTo16(register _cmsTRANSFORM* info,
                                   register cmsUInt16Number wIn[],
                                   register cmsUInt8Number* accum,
                                   register cmsUInt32Number Stride)
{
    if (T_PLANAR(info -> InputFormat)) {

        cmsFloat32Number* Pt = (cmsFloat32Number*) accum;
        cmsCIEXYZ XYZ;

        XYZ.X = Pt[0];
        XYZ.Y = Pt[Stride];
        XYZ.Z = Pt[Stride*2];
        cmsFloat2XYZEncoded(wIn, &XYZ);

        return accum + sizeof(cmsFloat32Number);

    }

    else {
        cmsFloat32Number* Pt = (cmsFloat32Number*) accum;
        cmsCIEXYZ XYZ;

        XYZ.X = Pt[0];
        XYZ.Y = Pt[1];
        XYZ.Z = Pt[2];
        cmsFloat2XYZEncoded(wIn, &XYZ);

        accum += 3 * sizeof(cmsFloat32Number) + T_EXTRA(info ->InputFormat) * sizeof(cmsFloat32Number);

        return accum;
    }
}
