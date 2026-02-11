setCurrentDate()
{
    OFString dicomDate;

    OFCondition l_error = getCurrentDate(dicomDate);
    if (l_error.good())
        l_error = putString(dicomDate.c_str());
    return l_error;
}
