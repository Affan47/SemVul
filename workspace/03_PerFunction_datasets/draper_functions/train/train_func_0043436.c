setTransientsOption(Options options)
{
    if (!m_realtime) {
        cerr << "RubberBandStretcher::Impl::setTransientsOption: Not permissible in non-realtime mode" << endl;
        return;
    }
    int mask = (OptionTransientsMixed | OptionTransientsSmooth | OptionTransientsCrisp);
    m_options &= ~mask;
    options &= mask;
    m_options |= options;

    m_stretchCalculator->setUseHardPeaks
        (!(m_options & OptionTransientsSmooth));
}
