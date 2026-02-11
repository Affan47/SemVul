ri_destructor(opal_object_t *obj)
{
  repository_item_t *ri = (repository_item_t *) obj;
  dependency_item_t *di;
  opal_list_item_t *item;
  int group_id;

  group_id = mca_base_var_group_find (NULL, ri->ri_type,
                                      ri->ri_component_struct->mca_component_name);
  if (0 <= group_id) {
    mca_base_var_group_deregister (group_id);
  }


  lt_dlclose(ri->ri_dlhandle);


  for (item = opal_list_remove_first(&ri->ri_dependencies);
       NULL != item;
       item = opal_list_remove_first(&ri->ri_dependencies)) {
    di = (dependency_item_t *) item;
    OBJ_RELEASE(di);
  }
  OBJ_DESTRUCT(&ri->ri_dependencies);
  opal_list_remove_item(&repository, (opal_list_item_t *) ri);
}
