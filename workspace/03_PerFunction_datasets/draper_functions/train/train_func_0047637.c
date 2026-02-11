is_supported_resolution(
    const float HWResolution[2]
)
{
    int     i;

    for (i = 0; i < countof(supported_resolutions); i++) {
        if (HWResolution[0] == supported_resolutions[i])
            return HWResolution[0] == HWResolution[1];
    }
    return false;
}
