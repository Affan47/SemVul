sscf_estab_req(SSCF_DSC *dsc,void *uu_data,int uu_length)
{
    switch (dsc->state) {
	case sscf_11:
	case sscf_34:
	    next_state(dsc,sscf_22);
	    sscop_estab_req(&dsc->sscop,uu_data,uu_length,1);
	    return;
	case sscf_410:
	    next_state(dsc,sscf_25);
	    sscop_res_req(&dsc->sscop,uu_data,uu_length);
	    return;
	default:
	    break;
    }
    diag(COMPONENT,DIAG_FATAL,"sscf_estab_req invoked in state %s",
      state_name[dsc->state]);
}
