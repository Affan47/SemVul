fill_cmd_dcmi_get_thermal_limit (uint8_t entity_id,
				 uint8_t entity_instance,
				 fiid_obj_t obj_cmd_rq)
{
  if ((entity_id != IPMI_DCMI_ENTITY_ID_INLET_TEMPERATURE
       && entity_id != IPMI_ENTITY_ID_AIR_INLET_B)
      || !fiid_obj_valid (obj_cmd_rq))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd_rq, tmpl_cmd_dcmi_get_thermal_limit_rq) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  FILL_FIID_OBJ_CLEAR (obj_cmd_rq);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "cmd", IPMI_CMD_DCMI_GET_THERMAL_LIMIT);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "group_extension_identification", IPMI_NET_FN_GROUP_EXTENSION_IDENTIFICATION_DCMI);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "entity_id", entity_id);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "entity_instance", entity_instance);

  return (0);
}
