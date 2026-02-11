sp_isexec(SP_STAT *info)
{


	if(info->s.st_mode&(0x00100|0x00001|0x00010)) return 1;
	return 0;
}
