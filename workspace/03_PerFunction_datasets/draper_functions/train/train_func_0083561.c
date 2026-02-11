PaUtil_DeviceIndexToHostApiDeviceIndex(
        PaDeviceIndex *hostApiDevice, PaDeviceIndex device, struct PaUtilHostApiRepresentation *hostApi )
{
    PaError result;
    PaDeviceIndex x;

    x = device - hostApi->privatePaFrontInfo.baseDeviceIndex;

    if( x < 0 || x >= hostApi->info.deviceCount )
    {
        result = paInvalidDevice;
    }
    else
    {
        *hostApiDevice = x;
        result = paNoError;
    }

    return result;
}
