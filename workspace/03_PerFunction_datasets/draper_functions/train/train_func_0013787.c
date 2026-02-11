MFBSetALUMode(alumode)

int alumode;


{
    int func;

    switch (alumode) {
    case MFBALUJAM:
        func = GXcopy;
        break;
    case MFBALUOR:
        func = GXor;
        break;
    case MFBALUNOR:
        func = GXnor;
        break;
    case MFBALUEOR:
        func = GXxor;
        break;
    default:
        return MFBBADALU;
        break;
    }
    XSetFunction(mfb_display, mfb_lineGC, func);
    XSetFunction(mfb_display, mfb_fillGC, func);
    mfb_curALUMode = alumode;
    return MFBOK;
}
