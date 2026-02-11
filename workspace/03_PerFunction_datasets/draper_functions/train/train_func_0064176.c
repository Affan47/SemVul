ms_obj_attr_new_array (MSObjAttrID id, GArray *array)
{
	MSObjAttr *res = g_new (MSObjAttr, 1);

	g_return_val_if_fail ((id & MS_OBJ_ATTR_MASK) == MS_OBJ_ATTR_IS_GARRAY_MASK, NULL);


	*((MSObjAttrID *)&(res->id)) = id;
	res->v.v_array = array;
	return res;
}
