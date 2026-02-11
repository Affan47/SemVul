_detailed_output_thresholds (ipmi_sensors_state_data_t *state_data,
                             const void *sdr_record,
                             unsigned int sdr_record_len,
                             const char *sensor_units_str)
{
  double *lower_non_critical_threshold = NULL;
  double *lower_critical_threshold = NULL;
  double *lower_non_recoverable_threshold = NULL;
  double *upper_non_critical_threshold = NULL;
  double *upper_critical_threshold = NULL;
  double *upper_non_recoverable_threshold = NULL;
  int rv = -1;

  assert (state_data);
  assert (sdr_record);
  assert (sdr_record_len);
  assert (sensor_units_str);
  assert (state_data->prog_data->args->verbose_count >= 1);

  if (ipmi_sensors_get_thresholds (state_data,
                                   sdr_record,
                                   sdr_record_len,
                                   &lower_non_critical_threshold,
                                   &lower_critical_threshold,
                                   &lower_non_recoverable_threshold,
                                   &upper_non_critical_threshold,
                                   &upper_critical_threshold,
                                   &upper_non_recoverable_threshold) < 0)
    goto cleanup;


  if (!lower_critical_threshold
      && !upper_critical_threshold
      && !lower_non_critical_threshold
      && !upper_non_critical_threshold
      && !lower_non_recoverable_threshold
      && !upper_non_recoverable_threshold)
    {
      rv = 0;
      goto cleanup;
    }

  if (lower_critical_threshold)
    pstdout_printf (state_data->pstate,
                    "Lower Critical Threshold: %f %s\n",
                    *lower_critical_threshold,
                    sensor_units_str);
  else
    pstdout_printf (state_data->pstate,
                    "Lower Critical Threshold: %s\n",
                    IPMI_SENSORS_NA_STRING_OUTPUT);

  if (upper_critical_threshold)
    pstdout_printf (state_data->pstate,
                    "Upper Critical Threshold: %f %s\n",
                    *upper_critical_threshold,
                    sensor_units_str);
  else
    pstdout_printf (state_data->pstate,
                    "Upper Critical Threshold: %s\n",
                    IPMI_SENSORS_NA_STRING_OUTPUT);

  if (lower_non_critical_threshold)
    pstdout_printf (state_data->pstate,
                    "Lower Non-Critical Threshold: %f %s\n",
                    *lower_non_critical_threshold,
                    sensor_units_str);
  else
    pstdout_printf (state_data->pstate,
                    "Lower Non-Critical Threshold: %s\n",
                    IPMI_SENSORS_NA_STRING_OUTPUT);

  if (upper_non_critical_threshold)
    pstdout_printf (state_data->pstate,
                    "Upper Non-Critical Threshold: %f %s\n",
                    *upper_non_critical_threshold,
                    sensor_units_str);
  else
    pstdout_printf (state_data->pstate,
                    "Upper Non-Critical Threshold: %s\n",
                    IPMI_SENSORS_NA_STRING_OUTPUT);

  if (lower_non_recoverable_threshold)
    pstdout_printf (state_data->pstate,
                    "Lower Non-Recoverable Threshold: %f %s\n",
                    *lower_non_recoverable_threshold,
                    sensor_units_str);
  else
    pstdout_printf (state_data->pstate,
                    "Lower Non-Recoverable Threshold: %s\n",
                    IPMI_SENSORS_NA_STRING_OUTPUT);

  if (upper_non_recoverable_threshold)
    pstdout_printf (state_data->pstate,
                    "Upper Non-Recoverable Threshold: %f %s\n",
                    *upper_non_recoverable_threshold,
                    sensor_units_str);
  else
    pstdout_printf (state_data->pstate,
                    "Upper Non-Recoverable Threshold: %s\n",
                    IPMI_SENSORS_NA_STRING_OUTPUT);

  rv = 0;
 cleanup:
  free (lower_non_critical_threshold);
  free (lower_critical_threshold);
  free (lower_non_recoverable_threshold);
  free (upper_non_critical_threshold);
  free (upper_critical_threshold);
  free (upper_non_recoverable_threshold);
  return (rv);
}
