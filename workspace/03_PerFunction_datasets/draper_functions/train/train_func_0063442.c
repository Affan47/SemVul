getStackRecursionLevel(void)


{
    int PopLevel, PopBrack, PPopLevel;

    PPopLevel = RecursionLevel;
    BasicPop(&PopLevel, &PopBrack);
    while (BasicPop(&PopLevel, &PopBrack) >= 0) {
        if (PopBrack < BraceLevel)
            break;

        PPopLevel = PopLevel;
    }
    BasicPush(PopLevel, PopBrack);
    BasicPush(PPopLevel, BraceLevel);
    return PPopLevel;
}
