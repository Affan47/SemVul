G_SerPortSetEvent( const INT16 dum_Handle, const WORD16 Event)
{
	int iRetour;
	WORD16 event = Event;

	if (port_fd < 0)
	{
		return GE_HOST_PORT_CLOSE;
	}
#ifdef _HPUX_SOURCE
	iRetour = ioctl(port_fd, MCGETA, &g_com_status);
#else
	iRetour = ioctl(port_fd, TIOCMGET, &g_com_status);
#endif

	if (iRetour == COM_C_system_error)
	{
		DEBUG_MSG("SerPortSetEvent error in ioctl");
		return GE_HOST_PARAMETERS;
	}

	switch (event)
	{
	case HGTSER_RI_LINE:
#ifdef _HPUX_SOURCE
		g_com_status |= MRI;
#elif _LINUX_SOURCE
		g_com_status |= TIOCM_RI;
#endif
		break;

	case HGTSER_DCD_LINE:
	case HGTSER_CTS_LINE:
	case HGTSER_DSR_LINE:
	default:
		break;
	}

	return G_OK;
}
