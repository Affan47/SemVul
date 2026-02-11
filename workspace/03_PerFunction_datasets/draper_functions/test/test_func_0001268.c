pvr2_ctrl_value_to_sym(struct pvr2_ctrl *cptr,
			   int mask,int val,
			   char *buf,unsigned int maxlen,
			   unsigned int *len)
{
	int ret;
	LOCK_TAKE(cptr->hdw->big_lock); do {
		ret = pvr2_ctrl_value_to_sym_internal(cptr,mask,val,
						      buf,maxlen,len);
	} while(0); LOCK_GIVE(cptr->hdw->big_lock);
	return ret;
}
