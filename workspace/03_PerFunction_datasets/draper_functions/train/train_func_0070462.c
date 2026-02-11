gf_sc_register_extra_graph(GF_Compositor *compositor, GF_SceneGraph *extra_scene, Bool do_remove)
{
	gf_sc_lock(compositor, 1);
	if (do_remove) gf_list_del_item(compositor->extra_scenes, extra_scene);
	else if (gf_list_find(compositor->extra_scenes, extra_scene)<0) gf_list_add(compositor->extra_scenes, extra_scene);
	gf_sc_lock(compositor, 0);
}
