HasFeature(Feature::Enum feature) const
{
    if (feature == Feature::Additional)
        return true;
    else
        return ListCtrlLogger::HasFeature(feature);
}
