display_intel_sr870bn4 (bmc_info_state_data_t *state_data, fiid_obj_t device_id_rs)
{
  uint8_t boot_code_major, boot_code_minor, pia_major, pia_minor;
  uint64_t val;
  fiid_obj_t obj_intel_rs = NULL;
  int rv = -1;

  assert (state_data);

  if (!(obj_intel_rs = fiid_obj_copy (device_id_rs, tmpl_cmd_get_device_id_sr870bn4_rs)))
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_copy: %s\n",
                       fiid_obj_errormsg (device_id_rs));
      goto cleanup;
    }

  if (FIID_OBJ_GET (obj_intel_rs,
                    "auxiliary_firmware_revision_information.boot_code.major",
                    &val) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_get: 'auxiliary_firmware_revision_information.boot_code.major': %s\n",
                       fiid_obj_errormsg (obj_intel_rs));
      goto cleanup;
    }
  boot_code_major = val;

  if (FIID_OBJ_GET (obj_intel_rs,
                    "auxiliary_firmware_revision_information.boot_code.minor",
                    &val) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_get: 'auxiliary_firmware_revision_information.boot_code.minor': %s\n",
                       fiid_obj_errormsg (obj_intel_rs));
      goto cleanup;
    }
  boot_code_minor = val;

  if (FIID_OBJ_GET (obj_intel_rs,
                    "auxiliary_firmware_revision_information.pia.major",
                    &val) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_get: 'auxiliary_firmware_revision_information.pia.major': %s\n",
                       fiid_obj_errormsg (obj_intel_rs));
      goto cleanup;
    }
  pia_major = val;

  if (FIID_OBJ_GET (obj_intel_rs,
                    "auxiliary_firmware_revision_information.pia.minor",
                    &val) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_get: 'auxiliary_firmware_revision_information.pia.minor': %s\n",
                       fiid_obj_errormsg (obj_intel_rs));
      goto cleanup;
    }
  pia_minor = val;

  pstdout_printf (state_data->pstate,
                  "Boot Code             : v%02x.%2x\n"
                  "PIA                   : v%02x.%2x\n",
                  boot_code_major,
                  boot_code_minor,
                  pia_major,
                  pia_minor);

  rv = 0;
 cleanup:
  fiid_obj_destroy (obj_intel_rs);
  return (rv);
}
