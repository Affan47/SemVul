AuSetComponentAttributes(AuUint8 * a, ComponentPtr c, AuUint8 * varData)
{
    AuUint32 mask, i;


    mask = COMMON(value_mask) & AuCompCommonMasks;
    i = 1;

    while (mask) {
        if (mask & 1)
            switch (i) {
            case AuCompCommonIDMask:
                c->id = COMMON(id);
                break;
            case AuCompCommonKindMask:
                c->kind = COMMON(kind);
                break;
            case AuCompCommonUseMask:
                c->use = COMMON(use);
                break;
            case AuCompCommonFormatMask:
                c->format = COMMON(format);
                break;
            case AuCompCommonNumTracksMask:
                c->numTracks = COMMON(num_tracks);
                break;
            case AuCompCommonAccessMask:
                c->access = COMMON(access);
                break;
            case AuCompCommonDescriptionMask:
                c->description.type = COMMON(description.type);
                c->description.len = COMMON(description.len);
                bcopy(varData, c->description.string, c->description.len);
                varData += PAD4(c->description.len);
                break;
            }

        mask >>= 1;
        i <<= 1;
    }


    i = (1L << 16);
    mask = COMMON(value_mask);

    switch (c->kind) {
    case AuComponentKindPhysicalInput:
    case AuComponentKindPhysicalOutput:
    case AuComponentKindPhysicalFeedback:
        mask = (mask & AuCompDeviceMasks) >> 16;

        while (mask) {
            if (mask & 1)
                switch (i) {
#if 0
                case AuCompDeviceMinSampleRateMask:
                    c->minSampleRate = DEVICE(min_sample_rate);
                    break;
                case AuCompDeviceMaxSampleRateMask:
                    c->maxSampleRate = DEVICE(max_sample_rate);
                    break;
                case AuCompDeviceLocationMask:
                    c->location = DEVICE(location);
                    break;
#endif
                case AuCompDeviceGainMask:
                    c->gain = DEVICE(gain);
                    break;
                case AuCompDeviceLineModeMask:
                    c->lineMode = DEVICE(line_mode);
                    break;
#if 0
                case AuCompDeviceChildrenMask:
                    break;
#endif
                }

            mask >>= 1;
            i <<= 1;
        }
        break;
    case AuComponentKindBucket:
        mask = (mask & AuCompBucketMasks) >> 16;

        while (mask) {
            if (mask & 1)
                switch (i) {
                case AuCompBucketSampleRateMask:
                    c->sampleRate = BUCKET(sample_rate);
                    break;
                case AuCompBucketNumSamplesMask:
                    c->numSamples = BUCKET(num_samples);
                    break;
                }

            mask >>= 1;
            i <<= 1;
        }
        break;
#ifdef NOTYET
    case AuComponentKindRadio:
        mask &= AuCompRadioMasks;

        while (mask) {
            switch (mask & 1) {
            }

            mask >>= 1;
            i <<= 1;
        }
        break;
#endif
    }

    return AuSuccess;
}
