Make_Pixel (unsigned long val) {
    Object pix;

    pix = Find_Object (T_Pixel, (GENERIC)0, Match_X_Obj, val);
    if (Nullp (pix)) {
        pix = Alloc_Object (sizeof (struct S_Pixel), T_Pixel, 0);
        PIXEL(pix)->tag = Null;
        PIXEL(pix)->pix = val;
        Register_Object (pix, (GENERIC)0, (PFO)0, 0);
    }
    return pix;
}
