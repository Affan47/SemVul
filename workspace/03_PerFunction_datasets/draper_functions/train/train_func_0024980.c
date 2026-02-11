bind_output (struct wl_client *client,
             void *data,
             uint32_t version,
             uint32_t id)
{
  CoglandOutput *output = data;
  struct wl_resource *resource =
    wl_client_add_object (client, &wl_output_interface, NULL, id, data);
  GList *l;

  wl_resource_post_event (resource,
                          WL_OUTPUT_GEOMETRY,
                          output->x, output->y,
                          output->width_mm,
                          output->height_mm,
                          0,
                          "unknown",
                          "unknown");

  for (l = output->modes; l; l = l->next)
    {
      CoglandMode *mode = l->data;
      wl_resource_post_event (resource,
                              WL_OUTPUT_MODE,
                              mode->flags,
                              mode->width,
                              mode->height,
                              mode->refresh);
    }
}
