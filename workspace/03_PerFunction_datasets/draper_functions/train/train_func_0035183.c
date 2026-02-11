intlinearize_free(itv_internal_t* intern,
		       itv_t* env, ap_dimension_t dim)
{
  if (env) itv_array_free(env,dim.intdim+dim.realdim);
  itv_internal_clear(intern);
}
