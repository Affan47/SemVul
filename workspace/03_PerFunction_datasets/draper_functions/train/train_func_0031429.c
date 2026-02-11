_config_file_sensor_types (struct conffile_data *data,
                           char *optionname,
                           char sensor_types[][CONFIG_FILE_MAX_SENSOR_TYPES_STRING_LENGTH+1],
                           unsigned int *sensor_types_length)
{
  unsigned int i;

  assert (data);
  assert (optionname);
  assert (sensor_types);
  assert (sensor_types_length);

  if (data->stringlist_len > CONFIG_FILE_MAX_SENSOR_TYPES)
    {
      fprintf (stderr, "Config File Error: invalid number of arguments for %s\n", optionname);
      exit (1);
    }

  for (i = 0; i < data->stringlist_len; i++)
    {
      if (strlen (data->stringlist[i]) > CONFIG_FILE_MAX_SENSOR_TYPES_STRING_LENGTH)
        {
          fprintf (stderr, "Config File Error: invalid value '%s' for %s\n",
                   data->stringlist[i],
                   optionname);
          exit (1);
        }

      strncpy (sensor_types[i],
               data->stringlist[i],
               CONFIG_FILE_MAX_SENSOR_TYPES_STRING_LENGTH);

      (*sensor_types_length)++;
    }

  return (0);
}
