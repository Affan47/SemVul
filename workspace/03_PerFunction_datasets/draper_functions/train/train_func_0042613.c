PrintPCSFloat(cmsFloat64Number Input[])
{
    if (Verbose > 1 && hTransXYZ && hTransLab) {

        cmsCIEXYZ XYZ = { 0, 0, 0 };
        cmsCIELab Lab = { 0, 0, 0 };

        if (hTransXYZ) cmsDoTransform(hTransXYZ, Input, &XYZ, 1);
        if (hTransLab) cmsDoTransform(hTransLab, Input, &Lab, 1);

        printf("[PCS] Lab=(%.4f,%.4f,%.4f) XYZ=(%.4f,%.4f,%.4f)\n", Lab.L, Lab.a, Lab.b,
            XYZ.X * 100.0, XYZ.Y * 100.0, XYZ.Z * 100.0);

    }
}
