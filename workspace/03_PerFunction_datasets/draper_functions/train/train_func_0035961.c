amitk_object_add_child(AmitkObject * object, AmitkObject * child) {

  g_return_if_fail(AMITK_IS_OBJECT(object));
  g_return_if_fail(AMITK_IS_OBJECT(child));


  g_return_if_fail(g_list_find(object->children, child) == NULL);


  g_return_if_fail(AMITK_OBJECT_PARENT(child) == NULL);

  g_signal_emit(G_OBJECT(object), object_signals[OBJECT_ADD_CHILD], 0, child);

  return;
}
