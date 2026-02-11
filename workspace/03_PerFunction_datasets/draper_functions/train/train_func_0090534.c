amitk_space_copy(const AmitkSpace * space) {

  AmitkSpace * new_space;

  g_return_val_if_fail(AMITK_IS_SPACE(space), NULL);

  new_space = amitk_space_new();
  amitk_space_copy_in_place(new_space, space);

  return new_space;
}
