fixup_flag(unsigned int idx)
{
	if (idx>MAX_FLAG) {
		LM_ERR("flag (%d) out of range %d..%d\n",
			idx, 0, MAX_FLAG );
		return 0;
	}
	return (1<<idx);
}
