construct(const std::set<size_t> &windowSizes,
                                                  size_t initialWindowSize,
                                                  size_t outbufSize)
{
    size_t maxSize = initialWindowSize;

    if (!windowSizes.empty()) {

        std::set<size_t>::const_iterator i = windowSizes.end();
        maxSize = *--i;
    }
    if (windowSizes.find(initialWindowSize) == windowSizes.end()) {
        if (initialWindowSize > maxSize) maxSize = initialWindowSize;
    }


    size_t realSize = (maxSize * oversample)/2 + 1;


    if (outbufSize < maxSize) outbufSize = maxSize;

    inbuf = new RingBuffer<float>(maxSize);
    outbuf = new RingBuffer<float>(outbufSize);

    mag = allocDouble(realSize);
    phase = allocDouble(realSize);
    prevPhase = allocDouble(realSize);
    prevError = allocDouble(realSize);
    unwrappedPhase = allocDouble(realSize);
    envelope = allocDouble(realSize);

    freqPeak = new size_t[realSize];

    fltbuf = allocFloat(maxSize);

    accumulator = allocFloat(maxSize);
    windowAccumulator = allocFloat(maxSize);

    for (std::set<size_t>::const_iterator i = windowSizes.begin();
         i != windowSizes.end(); ++i) {
        ffts[*i] = new FFT(*i * oversample);
        ffts[*i]->initDouble();
    }
    if (windowSizes.find(initialWindowSize) == windowSizes.end()) {
        ffts[initialWindowSize] = new FFT(initialWindowSize * oversample);
        ffts[initialWindowSize]->initDouble();
    }
    fft = ffts[initialWindowSize];

    dblbuf = fft->getDoubleTimeBuffer();

    resampler = 0;
    resamplebuf = 0;
    resamplebufSize = 0;

    reset();

    for (size_t i = 0; i < realSize; ++i) {
        freqPeak[i] = 0;
    }

    for (size_t i = 0; i < initialWindowSize * oversample; ++i) {
        dblbuf[i] = 0.0;
    }

    for (size_t i = 0; i < maxSize; ++i) {
        accumulator[i] = 0.f;
        windowAccumulator[i] = 0.f;
    }


    windowAccumulator[0] = 1.f;
}
