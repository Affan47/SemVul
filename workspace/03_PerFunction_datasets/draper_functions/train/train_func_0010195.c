CTXLoad_AttachScene(GF_SceneDecoder *plug, GF_Scene *scene, Bool is_scene_decoder)
{
	CTXLoadPriv *priv = (CTXLoadPriv *)plug->privateStack;
	if (priv->ctx) return GF_BAD_PARAM;

	priv->scene = scene;
	priv->app = scene->root_od->term;
	gf_sg_set_node_callback(scene->graph, CTXLoad_NodeCallback);

	return GF_OK;
}
