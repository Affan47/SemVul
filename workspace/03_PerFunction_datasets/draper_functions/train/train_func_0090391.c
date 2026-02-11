lockExclusive()
{
    if (pHandle && lockingMode) return EC_Normal;
    OFCondition result = EC_Normal;
    if (pHandle == NULL) result = lockDatabase();
    if (result.good())
    {

        pHandle->DB_unlock();
        if (pHandle->DB_lock(OFTrue).good())
            lockingMode = OFTrue;
        else
            result = EC_IllegalCall;
    }
    return result;
}
