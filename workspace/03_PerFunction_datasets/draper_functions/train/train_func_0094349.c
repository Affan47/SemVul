sscf_data_ind(void *user_data,void *data,int length,int sn)
{
    SSCF_DSC *dsc = user_data;

    if (dsc->state != sscf_410)
	diag(COMPONENT,DIAG_FATAL,"sscf_data_ind in state %s",
	  state_name[dsc->state]);
    if (dsc->ops->data_ind) dsc->ops->data_ind(dsc->user,data,length);

}
