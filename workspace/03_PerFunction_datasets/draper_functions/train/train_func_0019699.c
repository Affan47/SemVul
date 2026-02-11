vampInitialise(VampPluginHandle handle,
                                        unsigned int channels,
                                        unsigned int stepSize,
                                        unsigned int blockSize)
{
#ifdef DEBUG_PLUGIN_ADAPTER
    std::cerr << "PluginAdapterBase::Impl::vampInitialise(" << handle << ", " << channels << ", " << stepSize << ", " << blockSize << ")" << std::endl;
#endif

    Impl *adapter = lookupAdapter(handle);
    if (!adapter) return 0;
    bool result = ((Plugin *)handle)->initialise(channels, stepSize, blockSize);
    adapter->markOutputsChanged((Plugin *)handle);
    return result ? 1 : 0;
}
