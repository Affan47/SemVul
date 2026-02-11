alcCaptureOpenDevice(const ALCchar *deviceName, ALCuint frequency, ALCenum format, ALCsizei SampleSize)
{
    ALCdevice *device = NULL;
    ALCenum err;

    DO_INITCONFIG();

    if(!CaptureBackend.name)
    {
        alcSetError(NULL, ALC_INVALID_VALUE);
        return NULL;
    }

    if(SampleSize <= 0)
    {
        alcSetError(NULL, ALC_INVALID_VALUE);
        return NULL;
    }

    if(deviceName && (!deviceName[0] || strcasecmp(deviceName, alcDefaultName) == 0 || strcasecmp(deviceName, "openal-soft") == 0))
        deviceName = NULL;

    device = calloc(1, sizeof(ALCdevice));
    if(!device)
    {
        alcSetError(NULL, ALC_OUT_OF_MEMORY);
        return NULL;
    }


    device->Funcs = &CaptureBackend.Funcs;
    device->ref = 1;
    device->Connected = ALC_TRUE;
    device->Type = Capture;
    InitializeCriticalSection(&device->Mutex);

    InitUIntMap(&device->BufferMap, ~0);
    InitUIntMap(&device->EffectMap, ~0);
    InitUIntMap(&device->FilterMap, ~0);

    device->szDeviceName = NULL;

    device->Flags |= DEVICE_FREQUENCY_REQUEST;
    device->Frequency = frequency;

    device->Flags |= DEVICE_CHANNELS_REQUEST | DEVICE_SAMPLE_TYPE_REQUEST;
    if(DecomposeDevFormat(format, &device->FmtChans, &device->FmtType) == AL_FALSE)
    {
        DeleteCriticalSection(&device->Mutex);
        free(device);
        alcSetError(NULL, ALC_INVALID_ENUM);
        return NULL;
    }

    device->UpdateSize = SampleSize;
    device->NumUpdates = 1;

    LockLists();
    if((err=ALCdevice_OpenCapture(device, deviceName)) != ALC_NO_ERROR)
    {
        UnlockLists();
        DeleteCriticalSection(&device->Mutex);
        free(device);
        alcSetError(NULL, err);
        return NULL;
    }
    UnlockLists();

    do {
        device->next = DeviceList;
    } while(!CompExchangePtr((XchgPtr*)&DeviceList, device->next, device));

    TRACE("Created device %p\n", device);
    return device;
}
