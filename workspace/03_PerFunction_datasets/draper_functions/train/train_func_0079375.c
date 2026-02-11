st_theme_node_update_resources (StThemeNodePaintState *state,
                                StThemeNode           *node,
                                float                  width,
                                float                  height)
{
  gboolean had_prerendered_texture = FALSE;
  gboolean had_box_shadow = FALSE;
  StShadow *box_shadow_spec;

  g_return_if_fail (width > 0 && height > 0);


  if (state->prerendered_texture != COGL_INVALID_HANDLE)
    {
      cogl_handle_unref (state->prerendered_texture);
      state->prerendered_texture = COGL_INVALID_HANDLE;
      had_prerendered_texture = TRUE;
    }
  if (state->prerendered_material != COGL_INVALID_HANDLE)
    {
      cogl_handle_unref (state->prerendered_material);
      state->prerendered_material = COGL_INVALID_HANDLE;

      if (node->border_slices_texture == COGL_INVALID_HANDLE &&
          state->box_shadow_material != COGL_INVALID_HANDLE)
        {
          cogl_handle_unref (state->box_shadow_material);
          state->box_shadow_material = COGL_INVALID_HANDLE;
          had_box_shadow = TRUE;
        }
    }

  st_theme_node_paint_state_set_node (state, node);
  state->alloc_width = width;
  state->alloc_height = height;

  box_shadow_spec = st_theme_node_get_box_shadow (node);

  if (had_prerendered_texture)
    {
      state->prerendered_texture = st_theme_node_prerender_background (node, width, height);
      state->prerendered_material = _st_create_texture_material (state->prerendered_texture);
    }
  else
    {
      int corner_id;

      for (corner_id = 0; corner_id < 4; corner_id++)
        if (state->corner_material[corner_id] == COGL_INVALID_HANDLE)
          state->corner_material[corner_id] =
            st_theme_node_lookup_corner (node, width, height, corner_id);
    }

  if (had_box_shadow)
    state->box_shadow_material = _st_create_shadow_material (box_shadow_spec,
                                                             state->prerendered_texture);
}
