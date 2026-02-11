param_objects_set_default (GParamSpec * pspec, GValue * value)
{
  if (value->data[0].v_pointer != NULL)
    {
      g_free (value->data[0].v_pointer);
    }
  value->data[0].v_pointer = NULL;
}
