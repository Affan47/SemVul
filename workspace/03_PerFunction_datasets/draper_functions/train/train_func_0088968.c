read(DcmItem &dataset)
{

    OFString tmpString;
    OFCondition result = DSRTypes::getAndCheckStringValueFromDataset(dataset, DCM_TemporalRangeType, tmpString, "1", "1", "TCOORD content item");
    if (result.good())
    {
        TemporalRangeType = DSRTypes::enumeratedValueToTemporalRangeType(tmpString);

        if (TemporalRangeType == DSRTypes::TRT_invalid)
            DSRTypes::printUnknownValueWarningMessage("TemporalRangeType", tmpString.c_str());

        SamplePositionList.read(dataset);
        TimeOffsetList.read(dataset);
        DatetimeList.read(dataset);

        if (!checkData(TemporalRangeType, SamplePositionList, TimeOffsetList, DatetimeList))
            result = SR_EC_InvalidValue;
    }
    return result;
}
