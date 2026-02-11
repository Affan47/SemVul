lib3ds_camera_new(const char *name)
{
  Lib3dsCamera *camera;

  ASSERT(name);
  ASSERT(strlen(name)<64);

  camera=(Lib3dsCamera*)calloc(sizeof(Lib3dsCamera), 1);
  if (!camera) {
    return(0);
  }
  strcpy(camera->name, name);
  camera->fov=45.0f;
  return(camera);
}
