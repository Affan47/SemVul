capi_cmsg_header (_cmsg *cmsg, unsigned _ApplId,
				 _cbyte _Command, _cbyte _Subcommand,
				 _cword _Messagenumber, _cdword _Controller)
{
	if (loadlib() < 0)
		return 0;
	return fptr_capi_cmsg_header(cmsg, _ApplId,
				 _Command, _Subcommand,
				 _Messagenumber, _Controller);
}
