ex_buffer(eap)
    exarg_T	*eap;
{
    if (*eap->arg)
	eap->errmsg = e_trailing;
    else
    {
	if (eap->addr_count == 0)
	    goto_buffer(eap, DOBUF_CURRENT, FORWARD, 0);
	else
	    goto_buffer(eap, DOBUF_FIRST, FORWARD, (int)eap->line2);
    }
}
