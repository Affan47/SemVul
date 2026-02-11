expand_pre (char *croot, ichar_t *rootword, MASKTYPE mask[],
				int option, char *extra)
{
    int				entcount;
    int				explength;
    register struct flagent *
				flent;

    for (flent = m_pflaglist, entcount = m_numpflags, explength = 0;
      entcount > 0;
      flent++, entcount--)
	{
		if (TSTMASKBIT (mask, flent->flagbit))
			explength +=
			  pr_pre_expansion (croot, rootword, flent, mask, option, extra);
	}
    return explength;
}
