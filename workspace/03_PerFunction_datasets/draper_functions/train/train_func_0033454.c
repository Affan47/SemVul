GetSafestVersion(PlasmaVer ver) {
    if (ver <= pvPrime)
        return pvPrime;
    else if (ver == pvPots)
        return pvPots;
    else if (ver <= pvMoul)
        return pvMoul;
    else if (ver == pvEoa)
        return pvEoa;
    else if (ver == pvHex)
        return pvHex;
    else
        return pvUniversal;
}
