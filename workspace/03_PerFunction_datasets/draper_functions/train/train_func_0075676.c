getValueforDDL(const Uint16 ddl) const
{
    if ((LODValue != NULL) && (ddl < ValueCount))
        return LODValue[ddl];
    return -1;
}
