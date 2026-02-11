taito8741_hostcmd_r(I8741 *st)
{
	if(!(st->status & 0x04)) return -1;
	st->status &= 0xfb;
	return st->fromCmd;
}
