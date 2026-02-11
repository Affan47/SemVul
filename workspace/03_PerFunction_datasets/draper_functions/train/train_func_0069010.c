releaseDatabase()
{
    if (pHandle == NULL) return EC_Normal;
    OFCondition cond = pHandle->DB_unlock();
    if (cond.good())
    {
      delete pHandle;
      pHandle = NULL;
      clearIndexCache();
    }
    return cond;
}
