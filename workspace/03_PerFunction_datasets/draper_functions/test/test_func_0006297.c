compositor_init_timesensor(GF_Compositor *compositor, GF_Node *node)
{
	TimeSensorStack *st;
	GF_SAFEALLOC(st, TimeSensorStack);
	st->time_handle.UpdateTimeNode = timesensor_update_time;
	st->time_handle.udta = node;
	st->store_info = 1;
	st->compositor = compositor;
#ifndef GPAC_DISABLE_X3D
	st->is_x3d = (gf_node_get_tag(node)==TAG_X3D_TimeSensor) ? 1 : 0;
#endif
	gf_node_set_private(node, st);
	gf_node_set_callback_function(node, timesensor_destroy);


	gf_sc_register_time_node(compositor, &st->time_handle);
}
