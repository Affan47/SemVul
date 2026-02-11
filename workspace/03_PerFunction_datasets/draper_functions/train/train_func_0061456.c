makeFlatKernel(l_int32  height,
               l_int32  width,
               l_int32  cy,
               l_int32  cx)
{
l_int32    i, j;
l_float32  normval;
L_KERNEL  *kel;

    PROCNAME("makeFlatKernel");

    if ((kel = kernelCreate(height, width)) == NULL)
        return (L_KERNEL *)ERROR_PTR("kel not made", procName, NULL);
    kernelSetOrigin(kel, cy, cx);
    normval = 1.0 / (l_float32)(height * width);
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            kernelSetElement(kel, i, j, normval);
        }
    }

    return kel;
}
