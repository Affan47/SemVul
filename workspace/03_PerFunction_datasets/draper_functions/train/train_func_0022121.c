clutter_shader_effect_set_actor (ClutterActorMeta *meta,
                                 ClutterActor     *actor)
{
  ClutterShaderEffect *self = CLUTTER_SHADER_EFFECT (meta);
  ClutterShaderEffectPrivate *priv = self->priv;
  ClutterActorMetaClass *parent;

  if (!clutter_feature_available (CLUTTER_FEATURE_SHADERS_GLSL))
    {


      g_warning ("Unable to use the ShaderEffect: the graphics hardware "
                 "or the current GL driver does not implement support "
                 "for the GLSL shading language.");
      clutter_actor_meta_set_enabled (meta, FALSE);
      return;
    }

  parent = CLUTTER_ACTOR_META_CLASS (clutter_shader_effect_parent_class);
  parent->set_actor (meta, actor);


  priv->actor = clutter_actor_meta_get_actor (meta);
  if (priv->actor == NULL)
    return;

  CLUTTER_NOTE (SHADER, "Preparing shader effect of type '%s'",
                G_OBJECT_TYPE_NAME (meta));
}
