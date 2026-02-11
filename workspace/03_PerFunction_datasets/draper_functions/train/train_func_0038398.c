getOutputDescriptors() const
{
    OutputList list;

    OutputDescriptor sca;
    sca.identifier = "amplitude";
    sca.name = "Amplitude";
    sca.description = "";
    sca.unit = "V";
    sca.hasFixedBinCount = true;
    sca.binCount = 1;
    sca.hasKnownExtents = false;
    sca.isQuantized = false;
    sca.sampleType = OutputDescriptor::OneSamplePerStep;
    list.push_back(sca);

    return list;
}
