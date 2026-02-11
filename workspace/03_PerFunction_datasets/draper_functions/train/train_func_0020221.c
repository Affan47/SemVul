volume_copy(const AmitkObject * object) {

  AmitkVolume * copy;

  g_return_val_if_fail(AMITK_IS_VOLUME(object), NULL);

  copy = amitk_volume_new();

  amitk_object_copy_in_place(AMITK_OBJECT(copy), AMITK_OBJECT(object));

  return AMITK_OBJECT(copy);

}
