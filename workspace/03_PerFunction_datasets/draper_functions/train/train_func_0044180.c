globus_l_error_no_credentials_instance_data (globus_object_t *error)
{
  globus_error_no_credentials_instance_t * instance_data;
  globus_object_t * local_object;

  local_object
  = globus_object_upcast (error, GLOBUS_ERROR_TYPE_NO_CREDENTIALS);

  if (local_object==NULL) return NULL;

  instance_data
  = ((globus_error_no_credentials_instance_t *)
     globus_object_get_local_instance_data (local_object));

  if (instance_data!=NULL) return instance_data;
  else {
    instance_data
    = globus_malloc (sizeof(globus_error_no_credentials_instance_t));
    globus_object_set_local_instance_data (local_object,
                                           instance_data);

    instance_data->no_credentials_file = NULL;
    return instance_data;
  }
}
