globus_object_upcast (globus_object_t            * object,
		      const globus_object_type_t * desired_type)
{
  if ( globus_object_assert_valid (object)
       == GLOBUS_FALSE ) return NULL;

  if (desired_type==NULL) return NULL;

  while ( (object!=NULL) && (object->type!=desired_type) ) {
    object = object->parent_object;
  }

  if ( object!=NULL ) {
     return object;
   }
   else {
    return NULL;
  }
}
