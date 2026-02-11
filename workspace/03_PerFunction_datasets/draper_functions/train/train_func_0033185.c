probe_int13h_01h_fail(int istatus)
{
    int status = 0;

    if (istatus >= 256)
	status = istatus;
    else
	switch (istatus) {
	case 1: status = istatus;
	}
    return status;
}
