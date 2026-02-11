object_info_free (gpointer data)
{
  if (G_LIKELY (data))
    {
      ObjectInfo *oinfo = data;

      g_free (oinfo->id);
      g_free (oinfo->class_name);
      g_free (oinfo->type_func);

      g_list_foreach (oinfo->properties, (GFunc) property_info_free, NULL);
      g_list_free (oinfo->properties);

      g_list_foreach (oinfo->signals, (GFunc) signal_info_free, NULL);
      g_list_free (oinfo->signals);


      g_list_foreach (oinfo->children, (GFunc) g_free, NULL);
      g_list_free (oinfo->children);


      if (oinfo->object != NULL)
        {
          if (oinfo->is_unmerged)
            {
              if (oinfo->is_actor && !oinfo->is_stage)
                clutter_actor_destroy (CLUTTER_ACTOR (oinfo->object));
            }

          g_object_unref (oinfo->object);

          oinfo->object = NULL;
        }

      g_slice_free (ObjectInfo, oinfo);
    }
}
