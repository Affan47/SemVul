probe_rts8891_devices (void)
{

  SANEI_Config config;

  SANE_Option_Descriptor *options[NUM_CFG_OPTIONS];

  void *values[NUM_CFG_OPTIONS];
  int i;
  SANE_Status status;

  DBG (DBG_proc, "probe_rts8891_devices: start\n");


  rtscfg.allowsharing = SANE_FALSE;
  rtscfg.modelnumber = -1;
  rtscfg.sensornumber = -1;


  options[CFG_MODEL_NUMBER] =
    (SANE_Option_Descriptor *) malloc (sizeof (SANE_Option_Descriptor));
  options[CFG_MODEL_NUMBER]->name = "modelnumber";
  options[CFG_MODEL_NUMBER]->desc =
    "user provided scanner's internal model number";
  options[CFG_MODEL_NUMBER]->type = SANE_TYPE_INT;
  options[CFG_MODEL_NUMBER]->unit = SANE_UNIT_NONE;
  options[CFG_MODEL_NUMBER]->size = sizeof (SANE_Word);
  options[CFG_MODEL_NUMBER]->cap = SANE_CAP_SOFT_SELECT;
  options[CFG_MODEL_NUMBER]->constraint_type = SANE_CONSTRAINT_RANGE;
  options[CFG_MODEL_NUMBER]->constraint.range = &model_range;
  values[CFG_MODEL_NUMBER] = &rtscfg.modelnumber;

  options[CFG_ALLOW_SHARING] =
    (SANE_Option_Descriptor *) malloc (sizeof (SANE_Option_Descriptor));
  options[CFG_ALLOW_SHARING]->name = "allowsharing";
  options[CFG_ALLOW_SHARING]->desc =
    "allow sharing of the scanner by several frontends";
  options[CFG_ALLOW_SHARING]->type = SANE_TYPE_BOOL;
  options[CFG_ALLOW_SHARING]->unit = SANE_UNIT_NONE;
  options[CFG_ALLOW_SHARING]->size = sizeof (SANE_Bool);
  options[CFG_ALLOW_SHARING]->cap = SANE_CAP_SOFT_SELECT;
  options[CFG_ALLOW_SHARING]->constraint_type = SANE_CONSTRAINT_NONE;
  values[CFG_ALLOW_SHARING] = &rtscfg.allowsharing;


  options[CFG_SENSOR_NUMBER] =
    (SANE_Option_Descriptor *) malloc (sizeof (SANE_Option_Descriptor));
  options[CFG_SENSOR_NUMBER]->name = "sensornumber";
  options[CFG_SENSOR_NUMBER]->desc =
    "user provided scanner's internal sensor number";
  options[CFG_SENSOR_NUMBER]->type = SANE_TYPE_INT;
  options[CFG_SENSOR_NUMBER]->unit = SANE_UNIT_NONE;
  options[CFG_SENSOR_NUMBER]->size = sizeof (SANE_Word);
  options[CFG_SENSOR_NUMBER]->cap = SANE_CAP_SOFT_SELECT;
  options[CFG_SENSOR_NUMBER]->constraint_type = SANE_CONSTRAINT_RANGE;
  options[CFG_SENSOR_NUMBER]->constraint.range = &sensor_range;
  values[CFG_SENSOR_NUMBER] = &rtscfg.sensornumber;


  config.descriptors = options;
  config.values = values;
  config.count = NUM_CFG_OPTIONS;


  sanei_usb_init ();


  status = sanei_configure_attach (RTS8891_CONFIG_FILE, &config,
				   config_attach_rts8891);

  for (i = 0; i < NUM_CFG_OPTIONS; i++)
    {
      free (options[i]);
    }

  DBG (DBG_proc, "probe_rts8891_devices: end\n");
  return status;
}
