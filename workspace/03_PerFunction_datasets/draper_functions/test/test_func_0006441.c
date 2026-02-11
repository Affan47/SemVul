fill_cmd_get_payload_instance_info (uint8_t payload_type,
                                    uint8_t payload_instance,
                                    fiid_obj_t obj_cmd_rq)
{
  if (!IPMI_PAYLOAD_TYPE_VALID (payload_type)
      || !fiid_obj_valid (obj_cmd_rq))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd_rq, tmpl_cmd_get_payload_instance_info_rq) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  FILL_FIID_OBJ_CLEAR (obj_cmd_rq);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "cmd", IPMI_CMD_GET_PAYLOAD_INSTANCE_INFO);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "payload_type", payload_type);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "payload_instance", payload_instance);

  return (0);
}
