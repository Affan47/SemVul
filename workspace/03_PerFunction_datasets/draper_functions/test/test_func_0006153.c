spc_modesense_rwrecovery(struct se_cmd *cmd, u8 pc, u8 *p)
{
	p[0] = 0x01;
	p[1] = 0x0a;


	if (pc == 1)
		goto out;

out:
	return 12;
}
