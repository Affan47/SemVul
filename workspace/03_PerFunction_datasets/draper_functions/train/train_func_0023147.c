socket_resume_io(struct IPC_CHANNEL *ch)
{
	int		rc1 = IPC_OK;
	int		rc2 = IPC_OK;
	int		nwmsg = 1;
	int		nbytes_r = 1;
	gboolean	OKonce = FALSE;

	CHANAUDIT(ch);
	if (!IPC_ISRCONN(ch)) {
		return IPC_BROKEN;
	}

	do {
		if (nbytes_r > 0) {
			rc1 = socket_resume_io_read(ch, &nbytes_r, FALSE);
		}
		if (nwmsg > 0) {
			nwmsg = 0;
			rc2 = socket_resume_io_write(ch, &nwmsg);
		}
		if (rc1 == IPC_OK || rc2 == IPC_OK) {
			OKonce = TRUE;
		}
	} while ((nbytes_r > 0  || nwmsg > 0) && IPC_ISRCONN(ch));

	if (IPC_ISRCONN(ch)) {
		if (rc1 != IPC_OK) {
			cl_log(LOG_ERR
			       ,	"socket_resume_io_read() failure");
		}
		if (rc2 != IPC_OK && IPC_CONNECT == ch->ch_status) {
			cl_log(LOG_ERR
			,	"socket_resume_io_write() failure");
		}
	} else {
		return (OKonce ? IPC_OK : IPC_BROKEN);
	}

	return (rc1 != IPC_OK ? rc1 : rc2);
}
