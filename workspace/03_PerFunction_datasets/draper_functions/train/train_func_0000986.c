BilinearInterpFloat(const cmsFloat32Number Input[],
                         cmsFloat32Number Output[],
                         const cmsInterpParams* p)

{
#   define LERP(a,l,h)    (cmsFloat32Number) ((l)+(((h)-(l))*(a)))
#   define DENS(i,j)      (LutTable[(i)+(j)+OutChan])

    const cmsFloat32Number* LutTable = (cmsFloat32Number*) p ->Table;
    cmsFloat32Number      px, py;
    int        x0, y0,
               X0, Y0, X1, Y1;
    int        TotalOut, OutChan;
    cmsFloat32Number      fx, fy,
        d00, d01, d10, d11,
        dx0, dx1,
        dxy;

    TotalOut   = p -> nOutputs;
    px = Input[0] * p->Domain[0];
    py = Input[1] * p->Domain[1];

    x0 = (int) _cmsQuickFloor(px); fx = px - (cmsFloat32Number) x0;
    y0 = (int) _cmsQuickFloor(py); fy = py - (cmsFloat32Number) y0;

    X0 = p -> opta[1] * x0;
    X1 = X0 + (Input[0] >= 1.0 ? 0 : p->opta[1]);

    Y0 = p -> opta[0] * y0;
    Y1 = Y0 + (Input[1] >= 1.0 ? 0 : p->opta[0]);

    for (OutChan = 0; OutChan < TotalOut; OutChan++) {

        d00 = DENS(X0, Y0);
        d01 = DENS(X0, Y1);
        d10 = DENS(X1, Y0);
        d11 = DENS(X1, Y1);

        dx0 = LERP(fx, d00, d10);
        dx1 = LERP(fx, d01, d11);

        dxy = LERP(fy, dx0, dx1);

        Output[OutChan] = dxy;
    }


#   undef LERP
#   undef DENS
}
