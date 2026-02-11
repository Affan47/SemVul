calculateJNDBoundaries()
{
    if ((LODValue != NULL) && (ValueCount > 0))
    {
        if ((DeviceType == EDT_Printer) || (DeviceType == EDT_Scanner))
        {

            if (MaxDensity < 0)
                JNDMin = getJNDIndex(convertODtoLum(MaxValue));
            else
                JNDMin = getJNDIndex(convertODtoLum(MaxDensity));
            if (MinDensity < 0)
                JNDMax = getJNDIndex(convertODtoLum(MinValue));
            else
                JNDMax = getJNDIndex(convertODtoLum(MinDensity));
        } else {

            JNDMin = getJNDIndex(MinValue + AmbientLight);
            JNDMax = getJNDIndex(MaxValue + AmbientLight);
        }
        return (JNDMin >= 0) && (JNDMax >= 0);
    }
    return 0;
}
