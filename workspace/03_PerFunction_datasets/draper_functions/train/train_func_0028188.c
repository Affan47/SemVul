FindHostApi( PaDeviceIndex device, int *hostSpecificDeviceIndex )
{
    int i=0;

    if( !PA_IS_INITIALISED_ )
        return -1;

    if( device < 0 )
        return -1;

    while( i < paInternalInfo_.hostApisCount_
            && device >= paInternalInfo_.hostApis_[i]->info.deviceCount )
    {

        device -= paInternalInfo_.hostApis_[i]->info.deviceCount;
        ++i;
    }

    if( i >= paInternalInfo_.hostApisCount_ )
        return -1;

    if( hostSpecificDeviceIndex )
        *hostSpecificDeviceIndex = device;

    return i;
}
