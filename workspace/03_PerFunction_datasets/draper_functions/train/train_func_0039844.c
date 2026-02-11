pixRotateShear(PIX       *pixs,
               l_int32    xcen,
               l_int32    ycen,
               l_float32  angle,
               l_int32    incolor)
{
    PROCNAME("pixRotateShear");

    if (!pixs)
        return (PIX *)(PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (incolor != L_BRING_IN_WHITE && incolor != L_BRING_IN_BLACK)
        return (PIX *)(PIX *)ERROR_PTR("invalid incolor value", procName, NULL);

    if (L_ABS(angle) < MIN_ANGLE_TO_ROTATE)
        return pixClone(pixs);

    if (L_ABS(angle) <= MAX_2_SHEAR_ANGLE)
        return pixRotate2Shear(pixs, xcen, ycen, angle, incolor);

    if (L_ABS(angle) > LIMIT_SHEAR_ANGLE)
        L_WARNING("%6.2f radians; large angle for shear rotation\n",
                  procName, L_ABS(angle));
    return pixRotate3Shear(pixs, xcen, ycen, angle, incolor);
}
