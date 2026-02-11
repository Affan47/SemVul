delete_objects(ObjIO *obj)
{
  if (obj == NULL)
    return;
  else
    delete_objects(obj->next);

  if( obj->type == SPHERE_OBJ ) {
    delete_sphere((SphereIO *)obj->data);
  } else if( obj->type == POLYSET_OBJ ) {
    delete_poly_set((PolySetIO *)obj->data);
  } else {
    printf( "Error -- unrecognized object type\n" );
  }
  free(obj->material);
  if (obj->name != NULL) {
    free(obj->name);
  }
  free(obj);
}
