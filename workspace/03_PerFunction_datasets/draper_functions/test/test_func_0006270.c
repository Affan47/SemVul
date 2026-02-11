property_page_add_objbind(struct property_page *pp,
                                      gpointer object_data)
{
  struct objbind *ob;
  enum editor_object_type objtype;
  int id;

  if (!pp) {
    return;
  }

  objtype = property_page_get_objtype(pp);
  id = objtype_get_id_from_object(objtype, object_data);
  if (id < 0) {
    return;
  }

  if (objbind_hash_lookup(pp->objbind_table, id, NULL)) {

    return;
  }

  ob = objbind_new(objtype, object_data);
  if (!ob) {
    return;
  }

  objbind_bind_properties(ob, pp);

  objbind_hash_insert(pp->objbind_table, ob->object_id, ob);
}
