globus_error_get (globus_result_t result)
{
  globus_object_t * error;
  int err;

  if (! s_error_cache_initialized ) return NULL;

  if ( result == GLOBUS_SUCCESS ) return NULL;

  err = local_mutex_lock (&s_result_to_object_mutex);
  if (err) return NULL;

  error = globus_object_cache_remove (&s_result_to_object_mapper,
				      (void *)result);

  local_mutex_unlock (&s_result_to_object_mutex);

  if (error!=NULL)
    return error;
  else
    return GLOBUS_ERROR_NO_INFO;
}
