net_sendc(char c)
{
	if (c == '\r' && !linemode
#if defined(LOCAL_PROCESS)
				   && !local_process
#endif
						    ) {

		net_cookout("\r\0", 2);
	} else {
		net_cookout(&c, 1);
	}
}
