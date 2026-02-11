processDouble(const double *R__ mag, size_t increment)
{
    Profiler profiler("PercussiveAudioCurve::process");

    static double threshold = pow(10.0, 0.15);
    static double zeroThresh = pow(10.0, -8);

    size_t count = 0;
    size_t nonZeroCount = 0;

    const int sz = m_windowSize / 2;

    for (int n = 1; n <= sz; ++n) {
        bool above = ((mag[n] / m_prevMag[n]) >= threshold);
        if (above) ++count;
        if (mag[n] > zeroThresh) ++nonZeroCount;
    }

    for (int n = 1; n <= sz; ++n) {
	m_prevMag[n] = mag[n];
    }

    if (nonZeroCount == 0) return 0;
    else return float(count) / float(nonZeroCount);
}
