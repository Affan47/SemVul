e_modapi_init(E_Module *m)
{
   conf_face_edd = E_CONFIG_DD_NEW("Temperature_Config_Face", Config_Face);
#undef T
#undef D
#define T Config_Face
#define D conf_face_edd
   E_CONFIG_VAL(D, T, id, STR);
   E_CONFIG_VAL(D, T, poll_interval, INT);
   E_CONFIG_VAL(D, T, low, INT);
   E_CONFIG_VAL(D, T, high, INT);
   E_CONFIG_VAL(D, T, sensor_type, INT);
#ifdef HAVE_EEZE
   E_CONFIG_VAL(D, T, backend, INT);
#endif
   E_CONFIG_VAL(D, T, sensor_name, STR);
   E_CONFIG_VAL(D, T, units, INT);

   conf_edd = E_CONFIG_DD_NEW("Temperature_Config", Config);
#undef T
#undef D
#define T Config
#define D conf_edd
   E_CONFIG_HASH(D, T, faces, conf_face_edd);

   temperature_config = e_config_domain_load("module.temperature", conf_edd);
   if (!temperature_config)
     temperature_config = E_NEW(Config, 1);
   else
     eina_hash_foreach(temperature_config->faces, _temperature_face_id_max, &uuid);
   temperature_config->module = m;

   e_gadcon_provider_register(&_gadcon_class);
   return m;
}
