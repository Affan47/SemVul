amdlibFreeDarkData(amdlibDARK_DATA *dark)
{
    amdlibLogTrace("amdlibFreeDarkData()");

    if (dark->thisPtr != dark)
    {
        amdlibInitDarkData(dark);
        return;
    }

    amdlibFreeRegions(&dark->region, dark->nbRegions);
    amdlibFreeRegions(&dark->noise, dark->nbRegions);
    amdlibFreeRegions(&dark->otfBad, dark->nbRegions);
}
