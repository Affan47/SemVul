save_studio_room(void * context, ladish_room_handle room)
{
  uuid_t uuid;
  char str[37];

  log_info("saving room '%s'", ladish_room_get_name(room));

  if (!ladish_write_indented_string(fd, indent, "<room name=\""))
  {
    return false;
  }

  if (!ladish_write_string(fd, ladish_room_get_name(room)))
  {
    return false;
  }

  if (!ladish_write_string(fd, "\" uuid=\""))
  {
    return false;
  }

  ladish_room_get_uuid(room, uuid);
  uuid_unparse(uuid, str);

  if (!ladish_write_string(fd, str))
  {
    return false;
  }

  if (!ladish_write_string(fd, "\">\n"))
  {
    return false;
  }

  if (!ladish_write_room_link_ports(fd, indent + 1, room))
  {
    log_error("ladish_write_room_link_ports() failed");
    return false;
  }

  if (!ladish_write_indented_string(fd, indent, " </room>\n"))
  {
    return false;
  }

  return true;
}
