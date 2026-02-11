putString(const char *stringValue)
{
    OFCondition result = EC_Normal;

    clear();

    if ((stringValue != NULL) && (strlen(stringValue) > 0))
    {
        Float64 value = 0;
        OFBool success = OFFalse;
        const char *ptr = stringValue;

        while (result.good() && (ptr != NULL))
        {
            value = OFStandard::atof(ptr, &success);
            if (success)
            {
                addItem(value);

                ptr = strchr(ptr, ',');
                if (ptr != NULL)
                    ptr++;
            } else
                result = EC_CorruptedData;
        }
    }
    return result;
}
