initialise(size_t channels, size_t stepSize, size_t blockSize)
{
    if (m_d) {
	delete m_d;
	m_d = 0;
    }

    if (channels < getMinChannelCount() ||
	channels > getMaxChannelCount()) {
        std::cerr << "OnsetDetector::initialise: Unsupported channel count: "
                  << channels << std::endl;
        return false;
    }

    if (stepSize != getPreferredStepSize()) {
        std::cerr << "WARNING: OnsetDetector::initialise: Possibly sub-optimal step size for this sample rate: "
                  << stepSize << " (wanted " << (getPreferredStepSize()) << ")" << std::endl;
    }

    if (blockSize != getPreferredBlockSize()) {
        std::cerr << "WARNING: OnsetDetector::initialise: Possibly sub-optimal block size for this sample rate: "
                  << blockSize << " (wanted " << (getPreferredBlockSize()) << ")" << std::endl;
    }

    DFConfig dfConfig;
    dfConfig.DFType = m_dfType;
    dfConfig.stepSize = stepSize;
    dfConfig.frameLength = blockSize;
    dfConfig.dbRise = 6.0 - m_sensitivity / 16.6667;
    dfConfig.adaptiveWhitening = m_whiten;
    dfConfig.whiteningRelaxCoeff = -1;
    dfConfig.whiteningFloor = -1;

    m_d = new OnsetDetectorData(dfConfig);
    return true;
}
