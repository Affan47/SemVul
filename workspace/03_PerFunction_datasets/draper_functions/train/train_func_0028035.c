SB_Init(void)
{
    int i;
    int startLump;

    PatchH2BAR = W_CacheLumpName("H2BAR", PU_STATIC);
    PatchH2TOP = W_CacheLumpName("H2TOP", PU_STATIC);
    PatchINVBAR = W_CacheLumpName("INVBAR", PU_STATIC);
    PatchLFEDGE = W_CacheLumpName("LFEDGE", PU_STATIC);
    PatchRTEDGE = W_CacheLumpName("RTEDGE", PU_STATIC);
    PatchSTATBAR = W_CacheLumpName("STATBAR", PU_STATIC);
    PatchKEYBAR = W_CacheLumpName("KEYBAR", PU_STATIC);
    PatchSELECTBOX = W_CacheLumpName("SELECTBOX", PU_STATIC);
    PatchARTICLEAR = W_CacheLumpName("ARTICLS", PU_STATIC);
    PatchARMCLEAR = W_CacheLumpName("ARMCLS", PU_STATIC);
    PatchMANACLEAR = W_CacheLumpName("MANACLS", PU_STATIC);
    PatchMANAVIAL1 = W_CacheLumpName("MANAVL1", PU_STATIC);
    PatchMANAVIAL2 = W_CacheLumpName("MANAVL2", PU_STATIC);
    PatchMANAVIALDIM1 = W_CacheLumpName("MANAVL1D", PU_STATIC);
    PatchMANAVIALDIM2 = W_CacheLumpName("MANAVL2D", PU_STATIC);
    PatchMANADIM1 = W_CacheLumpName("MANADIM1", PU_STATIC);
    PatchMANADIM2 = W_CacheLumpName("MANADIM2", PU_STATIC);
    PatchMANABRIGHT1 = W_CacheLumpName("MANABRT1", PU_STATIC);
    PatchMANABRIGHT2 = W_CacheLumpName("MANABRT2", PU_STATIC);
    PatchINVLFGEM1 = W_CacheLumpName("invgeml1", PU_STATIC);
    PatchINVLFGEM2 = W_CacheLumpName("invgeml2", PU_STATIC);
    PatchINVRTGEM1 = W_CacheLumpName("invgemr1", PU_STATIC);
    PatchINVRTGEM2 = W_CacheLumpName("invgemr2", PU_STATIC);


    startLump = W_GetNumForName("IN0");
    for (i = 0; i < 10; i++)
    {
        PatchINumbers[i] = W_CacheLumpNum(startLump + i, PU_STATIC);
    }
    PatchNEGATIVE = W_CacheLumpName("NEGNUM", PU_STATIC);
    FontBNumBase = W_GetNumForName("FONTB16");
    startLump = W_GetNumForName("SMALLIN0");
    for (i = 0; i < 10; i++)
    {
        PatchSmNumbers[i] = W_CacheLumpNum(startLump + i, PU_STATIC);
    }
    PlayPalette = W_GetNumForName("PLAYPAL");
    SpinFlylump = W_GetNumForName("SPFLY0");
    SpinMinotaurLump = W_GetNumForName("SPMINO0");
    SpinSpeedLump = W_GetNumForName("SPBOOT0");
    SpinDefenseLump = W_GetNumForName("SPSHLD0");

    if (deathmatch)
    {
        PatchKILLS = W_CacheLumpName("KILLS", PU_STATIC);
    }
    SB_SetClassData();
}
