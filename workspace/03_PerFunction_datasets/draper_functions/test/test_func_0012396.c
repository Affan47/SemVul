hb_buffer_set_script (hb_buffer_t *buffer,
		      hb_script_t  script)
{
  if (unlikely (hb_object_is_inert (buffer)))
    return;

  buffer->props.script = script;
}
