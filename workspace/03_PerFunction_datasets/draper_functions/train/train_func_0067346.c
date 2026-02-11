champlain_view_ensure_layers_visible (ChamplainView *view,
    gboolean animate)
{
  DEBUG_LOG ()

  ClutterActorIter iter;
  ClutterActor *child;
  ChamplainBoundingBox *bbox;

  bbox = champlain_bounding_box_new ();

  clutter_actor_iter_init (&iter, view->priv->user_layers);
  while (clutter_actor_iter_next (&iter, &child))
    {
      ChamplainLayer *layer = CHAMPLAIN_LAYER (child);
      ChamplainBoundingBox *other;

      other = champlain_layer_get_bounding_box (layer);
      champlain_bounding_box_compose (bbox, other);
      champlain_bounding_box_free (other);
    }

  champlain_view_ensure_visible (view, bbox, animate);

  champlain_bounding_box_free (bbox);
}
