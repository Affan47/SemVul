alcGetString(ALCdevice *pDevice,ALCenum param)
{
    const ALCchar *value = NULL;

    switch(param)
    {
    case ALC_NO_ERROR:
        value = alcNoError;
        break;

    case ALC_INVALID_ENUM:
        value = alcErrInvalidEnum;
        break;

    case ALC_INVALID_VALUE:
        value = alcErrInvalidValue;
        break;

    case ALC_INVALID_DEVICE:
        value = alcErrInvalidDevice;
        break;

    case ALC_INVALID_CONTEXT:
        value = alcErrInvalidContext;
        break;

    case ALC_OUT_OF_MEMORY:
        value = alcErrOutOfMemory;
        break;

    case ALC_DEVICE_SPECIFIER:
        value = alcDefaultName;
        break;

    case ALC_ALL_DEVICES_SPECIFIER:
        if(VerifyDevice(pDevice))
        {
            value = pDevice->szDeviceName;
            ALCdevice_DecRef(pDevice);
        }
        else
        {
            ProbeAllDeviceList();
            value = alcAllDeviceList;
        }
        break;

    case ALC_CAPTURE_DEVICE_SPECIFIER:
        if(VerifyDevice(pDevice))
        {
            value = pDevice->szDeviceName;
            ALCdevice_DecRef(pDevice);
        }
        else
        {
            ProbeCaptureDeviceList();
            value = alcCaptureDeviceList;
        }
        break;


    case ALC_DEFAULT_DEVICE_SPECIFIER:
        value = alcDefaultName;
        break;

    case ALC_DEFAULT_ALL_DEVICES_SPECIFIER:
        if(!alcAllDeviceList)
            ProbeAllDeviceList();

        pDevice = VerifyDevice(pDevice);

        free(alcDefaultAllDeviceSpecifier);
        alcDefaultAllDeviceSpecifier = strdup(alcAllDeviceList ?
                                              alcAllDeviceList : "");
        if(!alcDefaultAllDeviceSpecifier)
            alcSetError(pDevice, ALC_OUT_OF_MEMORY);

        value = alcDefaultAllDeviceSpecifier;
        if(pDevice) ALCdevice_DecRef(pDevice);
        break;

    case ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER:
        if(!alcCaptureDeviceList)
            ProbeCaptureDeviceList();

        pDevice = VerifyDevice(pDevice);

        free(alcCaptureDefaultDeviceSpecifier);
        alcCaptureDefaultDeviceSpecifier = strdup(alcCaptureDeviceList ?
                                                  alcCaptureDeviceList : "");
        if(!alcCaptureDefaultDeviceSpecifier)
            alcSetError(pDevice, ALC_OUT_OF_MEMORY);

        value = alcCaptureDefaultDeviceSpecifier;
        if(pDevice) ALCdevice_DecRef(pDevice);
        break;

    case ALC_EXTENSIONS:
        if(!VerifyDevice(pDevice))
            value = alcNoDeviceExtList;
        else
        {
            value = alcExtensionList;
            ALCdevice_DecRef(pDevice);
        }
        break;

    default:
        pDevice = VerifyDevice(pDevice);
        alcSetError(pDevice, ALC_INVALID_ENUM);
        if(pDevice) ALCdevice_DecRef(pDevice);
        break;
    }

    return value;
}
