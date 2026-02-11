process(const float *const *inputBuffers,
                           Vamp::RealTime )
{
    if (m_stepSize == 0) {
	cerr << "ERROR: AmplitudeFollower::process: "
	     << "AmplitudeFollower has not been initialised"
	     << endl;
	return FeatureSet();
    }

    float previn = m_previn;

    FeatureSet returnFeatures;

    float val;
    float peak = 0.0f;

    for (size_t i = 0; i < m_stepSize; ++i) {

        val = fabs(inputBuffers[0][i]);

        if (val < previn) {
            val = val + (previn - val) * m_relaxcoef;
        } else {
            val = val + (previn - val) * m_clampcoef;
        }

        if (val > peak) peak = val;
        previn = val;
    }

    m_previn = previn;


    Feature feature;
    feature.hasTimestamp = false;
    feature.values.push_back(peak);
    returnFeatures[0].push_back(feature);

    return returnFeatures;
}
