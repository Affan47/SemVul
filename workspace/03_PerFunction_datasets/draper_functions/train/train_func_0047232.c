gegl_node_add_pad (GeglNode *self,
                   GeglPad  *pad)
{
  g_return_if_fail (GEGL_IS_NODE (self));
  g_return_if_fail (GEGL_IS_PAD (pad));

  if (gegl_node_get_pad (self, gegl_pad_get_name (pad)))
    return;

  self->pads = g_slist_prepend (self->pads, pad);

  if (gegl_pad_is_output (pad))
    self->output_pads = g_slist_prepend (self->output_pads, pad);

  if (gegl_pad_is_input (pad))
    self->input_pads = g_slist_prepend (self->input_pads, pad);
}
