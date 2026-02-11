_ml_P_Error_errmsg (ml_state_t *msp, ml_val_t arg)
{
    int		    errnum = INT_MLtoC(arg);
    ml_val_t	    s;

#if defined(HAS_STRERROR)
    char	    *msg = strerror(errnum);
    if (msg != 0)
	s = ML_CString (msp, msg);
    else {
	char		buf[64];
	sprintf(buf, "<unknown error %d>", errnum);
	s = ML_CString (msp, buf);
    }
#else
    if ((0 <= errnum) && (errnum < sys_nerr))
	s = ML_CString (msp, sys_errlist[errnum]);
    else {
	char		buf[64];
	sprintf(buf, "<unknown error %d>", errnum);
	s = ML_CString (msp, buf);
    }
#endif

    return s;

}
