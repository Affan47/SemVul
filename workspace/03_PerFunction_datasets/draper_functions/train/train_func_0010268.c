instanceReviewed(int pos)
{
    lockDatabase();
    OFBool wasNew = newInstancesReceived();
    if (pHandle == NULL) return EC_IllegalCall;
    OFCondition result = pHandle->instanceReviewed(pos);
    if (!wasNew) resetDatabaseReferenceTime();
    releaseDatabase();
    return result;
}
