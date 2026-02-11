ajCodBase(ajint c)
{
    ajint v;

    v = ajBaseAlphaToBin(c);

    if(v & 1)
        return 0;

    if(v & 2)
        return 1;

    if(v & 4)
        return 2;

    if(v & 8)
        return 3;

    return 0;
}
