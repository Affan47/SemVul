fill_cmd_set_system_boot_options_boot_info_acknowledge (uint8_t parameter_valid,
                                                        const uint8_t *bios_or_post_handled_boot_info,
                                                        const uint8_t *os_loader_handled_boot_info,
                                                        const uint8_t *os_or_service_partition_handled_boot_info,
                                                        const uint8_t *sms_handled_boot_info,
                                                        const uint8_t *oem_handled_boot_info,
                                                        fiid_obj_t obj_cmd_rq)
{
  if (!IPMI_SYSTEM_BOOT_OPTIONS_PARAMETER_VALID_VALID (parameter_valid)
      || (bios_or_post_handled_boot_info
          && !IPMI_SYSTEM_BOOT_OPTION_ENABLE_VALID (*bios_or_post_handled_boot_info))
      || (os_loader_handled_boot_info
          && !IPMI_SYSTEM_BOOT_OPTION_ENABLE_VALID (*os_loader_handled_boot_info))
      || (os_or_service_partition_handled_boot_info
          && !IPMI_SYSTEM_BOOT_OPTION_ENABLE_VALID (*os_or_service_partition_handled_boot_info))
      || (sms_handled_boot_info
          && !IPMI_SYSTEM_BOOT_OPTION_ENABLE_VALID (*sms_handled_boot_info))
      || (oem_handled_boot_info
          && !IPMI_SYSTEM_BOOT_OPTION_ENABLE_VALID (*oem_handled_boot_info))
      || !fiid_obj_valid (obj_cmd_rq))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd_rq, tmpl_cmd_set_system_boot_options_boot_info_acknowledge_rq) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  FILL_FIID_OBJ_CLEAR (obj_cmd_rq);

  FILL_FIID_OBJ_SET (obj_cmd_rq, "cmd", IPMI_CMD_SET_SYSTEM_BOOT_OPTIONS);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "parameter_selector", IPMI_SYSTEM_BOOT_OPTION_PARAMETER_BOOT_INFO_ACKNOWLEDGE);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "parameter_valid", parameter_valid);

  if (bios_or_post_handled_boot_info)
    {
      FILL_FIID_OBJ_SET (obj_cmd_rq, "enable_write_bit_0", IPMI_SYSTEM_BOOT_OPTION_ENABLE);
      FILL_FIID_OBJ_SET (obj_cmd_rq, "bios_or_post_handled_boot_info", *bios_or_post_handled_boot_info);
    }
  else
    {
      FILL_FIID_OBJ_SET (obj_cmd_rq, "enable_write_bit_0", IPMI_SYSTEM_BOOT_OPTION_DISABLE);
      FILL_FIID_OBJ_SET (obj_cmd_rq, "bios_or_post_handled_boot_info", IPMI_SYSTEM_BOOT_OPTION_BOOT_INFO_UNACKNOWLEDGE);
    }

  if (os_loader_handled_boot_info)
    {
      FILL_FIID_OBJ_SET (obj_cmd_rq, "enable_write_bit_1", IPMI_SYSTEM_BOOT_OPTION_ENABLE);
      FILL_FIID_OBJ_SET (obj_cmd_rq, "os_loader_handled_boot_info", *os_loader_handled_boot_info);
    }
  else
    {
      FILL_FIID_OBJ_SET (obj_cmd_rq, "enable_write_bit_1", IPMI_SYSTEM_BOOT_OPTION_DISABLE);
      FILL_FIID_OBJ_SET (obj_cmd_rq, "os_loader_handled_boot_info", IPMI_SYSTEM_BOOT_OPTION_BOOT_INFO_UNACKNOWLEDGE);
    }

  if (os_or_service_partition_handled_boot_info)
    {
      FILL_FIID_OBJ_SET (obj_cmd_rq, "enable_write_bit_2", IPMI_SYSTEM_BOOT_OPTION_ENABLE);
      FILL_FIID_OBJ_SET (obj_cmd_rq, "os_or_service_partition_handled_boot_info", *os_or_service_partition_handled_boot_info);
    }
  else
    {
      FILL_FIID_OBJ_SET (obj_cmd_rq, "enable_write_bit_2", IPMI_SYSTEM_BOOT_OPTION_DISABLE);
      FILL_FIID_OBJ_SET (obj_cmd_rq, "os_or_service_partition_handled_boot_info", IPMI_SYSTEM_BOOT_OPTION_BOOT_INFO_UNACKNOWLEDGE);
    }

  if (sms_handled_boot_info)
    {
      FILL_FIID_OBJ_SET (obj_cmd_rq, "enable_write_bit_3", IPMI_SYSTEM_BOOT_OPTION_ENABLE);
      FILL_FIID_OBJ_SET (obj_cmd_rq, "sms_handled_boot_info", *sms_handled_boot_info);
    }
  else
    {
      FILL_FIID_OBJ_SET (obj_cmd_rq, "enable_write_bit_3", IPMI_SYSTEM_BOOT_OPTION_DISABLE);
      FILL_FIID_OBJ_SET (obj_cmd_rq, "sms_handled_boot_info", IPMI_SYSTEM_BOOT_OPTION_BOOT_INFO_UNACKNOWLEDGE);
    }

  if (oem_handled_boot_info)
    {
      FILL_FIID_OBJ_SET (obj_cmd_rq, "enable_write_bit_4", IPMI_SYSTEM_BOOT_OPTION_ENABLE);
      FILL_FIID_OBJ_SET (obj_cmd_rq, "oem_handled_boot_info", *oem_handled_boot_info);
    }
  else
    {
      FILL_FIID_OBJ_SET (obj_cmd_rq, "enable_write_bit_4", IPMI_SYSTEM_BOOT_OPTION_DISABLE);
      FILL_FIID_OBJ_SET (obj_cmd_rq, "oem_handled_boot_info", IPMI_SYSTEM_BOOT_OPTION_BOOT_INFO_UNACKNOWLEDGE);
    }

  FILL_FIID_OBJ_SET (obj_cmd_rq, "enable_write_bit_5", IPMI_SYSTEM_BOOT_OPTION_ENABLE);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "enable_write_bit_6", IPMI_SYSTEM_BOOT_OPTION_ENABLE);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "enable_write_bit_7", IPMI_SYSTEM_BOOT_OPTION_ENABLE);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved", 0x7);
  return (0);
}
