GetNextFamilyName
(
    FAMILY_HANDLE& theFamilyHandle
) const
{
    TRACE("PF::GetNextFamilyName()\n");
    if (nextFamily(theFamilyHandle))
    {
        return getPrinterProxy(theFamilyHandle)->GetFamilyName();
    }
    else
    {
        return NULL;
    }
}
