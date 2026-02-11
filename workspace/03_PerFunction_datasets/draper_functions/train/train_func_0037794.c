globus_l_object_local_identity_instance_data (globus_object_t *object)
{
  globus_object_local_identity_instance_t * instance_data;
  globus_object_t * local_object;

  local_object
  = globus_object_upcast (object, GLOBUS_OBJECT_TYPE_LOCAL_IDENTITY);

  if (local_object==NULL) return NULL;

  instance_data
  = ((globus_object_local_identity_instance_t *)
     globus_object_get_local_instance_data (local_object));

  if (instance_data!=NULL) return instance_data;
  else {
    instance_data
    = globus_malloc (sizeof(globus_object_local_identity_instance_t));
    globus_object_set_local_instance_data (local_object,
                                           instance_data);

    instance_data->local_identity_computer = NULL;
    instance_data->local_identity_username = NULL;
    return instance_data;
  }
}
