capi20_register (unsigned MaxB3Connection,
				 unsigned MaxB3Blks,
				 unsigned MaxSizeB3,
				 unsigned *ApplID)
{
	if (loadlib() < 0)
		return CapiRegNotInstalled;
	return fptr_capi20_register(MaxB3Connection,
					 MaxB3Blks, MaxSizeB3, ApplID);
}
