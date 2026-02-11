ecGetAffine25519(const EcCurve *curve, EcPoint *R, const EcPoint *P)
{
    if (R != P) {
        bnCopy(R->x, P->x);
        bnCopy(R->y, P->y);
        bnCopy(R->z, P->z);
    }
    return 0;
}
