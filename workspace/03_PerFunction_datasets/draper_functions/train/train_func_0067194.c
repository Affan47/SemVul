dxf_object_append(DxfGlobalData *global,
	DxfLocalData *local, G3DObject *object)
{
	if(local->edata->block)
		local->edata->block->objects = g_slist_append(
			local->edata->block->objects, object);
	else
		global->model->objects = g_slist_append(global->model->objects,
			object);
}
