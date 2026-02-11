getISOFormattedTimeFromString(const OFString &dicomTime,
                                                   OFString &formattedTime,
                                                   const OFBool seconds,
                                                   const OFBool fraction,
                                                   const OFBool createMissingPart,
                                                   const OFBool supportOldFormat)
{
    OFCondition result = EC_Normal;
    if (!dicomTime.empty())
    {

        if (supportOldFormat || (dicomTime.find(":") == OFString_npos))
        {
            const size_t length = dicomTime.length();

            const size_t minPos = (supportOldFormat && (length > 2) && (dicomTime[2] == ':')) ? 3 : 2;
            const size_t secPos = (supportOldFormat && (length > minPos + 2) && (dicomTime[minPos + 2] == ':')) ? minPos + 3 : minPos + 2;

            const size_t decPoint = dicomTime.find(".");
            const size_t decLength = (decPoint != OFString_npos) ? decPoint : length;
            OFString hourStr, minStr, secStr, fracStr;

            if (decLength >= 2)
                hourStr = dicomTime.substr(0, 2);
            else
                hourStr = "00";

            if (decLength >= minPos + 2)
                minStr = dicomTime.substr(minPos, 2);
            else
                minStr = "00";

            if (decLength >= secPos + 2)
                secStr = dicomTime.substr(secPos, 2);
            else if (createMissingPart)
                secStr = "00";

            if ((length >= secPos + 4) && (decPoint == secPos + 2))
            {
                if (length < secPos + 9)
                {
                    fracStr = dicomTime.substr(secPos + 3);
                    fracStr.append(secPos + 9 - length, '0');
                } else
                    fracStr = dicomTime.substr(secPos + 3, 6);
            } else if (createMissingPart)
                fracStr = "000000";

            formattedTime = hourStr;
            formattedTime += ":";
            formattedTime += minStr;
            if (seconds && !secStr.empty())
            {
                formattedTime += ":";
                formattedTime += secStr;
                if (fraction && !fracStr.empty())
                {
                    formattedTime += ".";
                    formattedTime += fracStr;
                }
            }
            result = EC_Normal;
        } else {

            result = EC_IllegalParameter;
        }

        if (result.bad())
            formattedTime.clear();
    } else {

        formattedTime.clear();
    }
    return result;
}
