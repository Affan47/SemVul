ap_abstract0_check_dim(ap_funid_t funid, ap_manager_t* man,
			    ap_dimension_t dimension, ap_dim_t dim)
{
  if (dim>=dimension.intdim+dimension.realdim){
    ap_abstract0_check_dim_raise(funid,man,dimension,dim,
				 "incompatible dimension for the abstract value");
    return false;
  } else {
    return true;
  }
}
