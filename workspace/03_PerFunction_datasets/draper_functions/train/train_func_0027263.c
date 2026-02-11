hwloc_distances_set_from_env(struct hwloc_topology *topology)
{
  hwloc_obj_type_t type;
  for(type = HWLOC_OBJ_SYSTEM; type < HWLOC_OBJ_TYPE_MAX; type++) {
    char *env, envname[64];
    snprintf(envname, sizeof(envname), "HWLOC_%s_DISTANCES", hwloc_obj_type_string(type));
    env = getenv(envname);
    if (env) {
      hwloc_localeswitch_declare;
      hwloc_localeswitch_init();
      hwloc_distances__set_from_string(topology, type, env);
      hwloc_localeswitch_fini();
    }
  }
}
