st_widget_get_theme_node (StWidget *widget)
{
  StWidgetPrivate *priv = widget->priv;

  if (priv->theme_node == NULL)
    {
      StThemeContext *context;
      StThemeNode *tmp_node;
      StThemeNode *parent_node = NULL;
      ClutterStage *stage = NULL;
      ClutterActor *parent;
      char *pseudo_class, *direction_pseudo_class;

      parent = clutter_actor_get_parent (CLUTTER_ACTOR (widget));
      while (parent != NULL)
        {
          if (parent_node == NULL && ST_IS_WIDGET (parent))
            parent_node = st_widget_get_theme_node (ST_WIDGET (parent));
          else if (CLUTTER_IS_STAGE (parent))
            stage = CLUTTER_STAGE (parent);

          parent = clutter_actor_get_parent (parent);
        }

      if (stage == NULL)
        {
          g_critical ("st_widget_get_theme_node called on the widget %s which is not in the stage.",
                      st_describe_actor (CLUTTER_ACTOR (widget)));
          return g_object_new (ST_TYPE_THEME_NODE, NULL);
        }

      if (parent_node == NULL)
        parent_node = get_root_theme_node (CLUTTER_STAGE (stage));


      if (clutter_actor_get_text_direction (CLUTTER_ACTOR (widget)) == CLUTTER_TEXT_DIRECTION_RTL)
        direction_pseudo_class = "rtl";
      else
        direction_pseudo_class = "ltr";

      if (priv->pseudo_class)
        pseudo_class = g_strconcat(priv->pseudo_class, " ",
                                   direction_pseudo_class, NULL);
      else
        pseudo_class = direction_pseudo_class;

      context = st_theme_context_get_for_stage (stage);
      tmp_node = st_theme_node_new (context, parent_node, priv->theme,
                                    G_OBJECT_TYPE (widget),
                                    clutter_actor_get_name (CLUTTER_ACTOR (widget)),
                                    priv->style_class,
                                    pseudo_class,
                                    priv->inline_style);

      if (pseudo_class != direction_pseudo_class)
        g_free (pseudo_class);

      priv->theme_node = g_object_ref (st_theme_context_intern_node (context,
                                                                     tmp_node));
      g_object_unref (tmp_node);
    }

  return priv->theme_node;
}
