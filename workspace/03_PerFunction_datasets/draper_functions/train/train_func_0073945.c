replacement_block_init (ReplacementBlock *block,
                        DBusTypeReader   *reader)
{
  if (!_dbus_string_init (&block->replacement))
    return FALSE;


  block->padding = reader->value_pos % 8;

  if (!_dbus_string_lengthen (&block->replacement, block->padding))
    goto oom;

  return TRUE;

 oom:
  _dbus_string_free (&block->replacement);
  return FALSE;
}
