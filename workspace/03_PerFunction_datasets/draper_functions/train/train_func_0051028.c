GetOffset(int* pbSuccess)
{
    const TerragenDataset& ds = *(TerragenDataset *) poDS;
	if(pbSuccess != NULL)
		*pbSuccess = TRUE;
	return ds.m_dOffset;
}
