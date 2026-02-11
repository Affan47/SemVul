ODF_AttachScene(GF_SceneDecoder *plug, GF_Scene *scene, Bool is_inline_scene)
{
	ODPriv *priv = (ODPriv *)plug->privateStack;
	if (priv && !priv->scene) priv->scene = scene;
	return GF_OK;
}
