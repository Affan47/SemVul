fill_cmd_suspend_resume_payload_encryption (uint8_t payload_type,
                                            uint8_t payload_instance,
                                            uint8_t operation,
                                            fiid_obj_t obj_cmd_rq)
{
  if (!IPMI_PAYLOAD_TYPE_VALID (payload_type)
      || !IPMI_SUSPEND_RESUME_PAYLOAD_ENCRYPTION_OPERATION_VALID (operation)
      || !fiid_obj_valid (obj_cmd_rq))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd_rq, tmpl_cmd_suspend_resume_payload_encryption_rq) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  FILL_FIID_OBJ_CLEAR (obj_cmd_rq);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "cmd", IPMI_CMD_SUSPEND_RESUME_PAYLOAD_ENCRYPTION);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "payload_type", payload_type);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved1", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "payload_instance", payload_instance);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved2", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "operation", operation);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved3", 0);

  return (0);
}
