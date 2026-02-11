fill_cmd_oem_intel_node_manager_enable_disable_node_manager_policy_control (uint8_t policy_enable_disable,
                                                                            uint8_t domain_id,
                                                                            uint8_t policy_id,
                                                                            fiid_obj_t obj_cmd_rq)
{
  if (!IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLE_DISABLE_VALID (policy_enable_disable)
      || !IPMI_OEM_INTEL_NODE_MANAGER_DOMAIN_ID_VALID (domain_id)
      || !fiid_obj_valid (obj_cmd_rq))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd_rq, tmpl_cmd_oem_intel_node_manager_enable_disable_node_manager_policy_control_rq) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  FILL_FIID_OBJ_CLEAR (obj_cmd_rq);

  FILL_FIID_OBJ_SET (obj_cmd_rq, "cmd", IPMI_CMD_OEM_INTEL_NODE_MANAGER_ENABLE_DISABLE_NODE_MANAGER_POLICY_CONTROL);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "manufacturer_id", IPMI_IANA_ENTERPRISE_ID_INTEL);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "policy_enable_disable", policy_enable_disable);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved1", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "domain_id", domain_id);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved2", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "policy_id", policy_id);

  return (0);
}
