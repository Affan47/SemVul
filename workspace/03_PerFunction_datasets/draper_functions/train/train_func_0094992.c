rawData(int lineNumber, int rawDataIndex) const
{

    if (!IN_RANGE_STRICT_MAX(lineNumber, 0, _lines.count()))
        return QString::null;


    const QStringList &rawData = _lines.value(lineNumber);
    if (!IN_RANGE_STRICT_MAX(rawDataIndex, 0, rawData.count()))
        return QString::null;


    return rawData.value(rawDataIndex);
}
