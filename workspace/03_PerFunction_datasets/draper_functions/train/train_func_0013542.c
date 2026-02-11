hwloc_backend_enable(struct hwloc_topology *topology, struct hwloc_backend *backend)
{
  struct hwloc_backend **pprev;


  if (backend->flags & (~(HWLOC_BACKEND_FLAG_NEED_LEVELS))) {
    fprintf(stderr, "Cannot enable %s discovery component `%s' with unknown flags %lx\n",
	    hwloc_disc_component_type_string(backend->component->type), backend->component->name, backend->flags);
    return -1;
  }


  pprev = &topology->backends;
  while (NULL != *pprev) {
    if ((*pprev)->component == backend->component) {
      if (hwloc_components_verbose)
	fprintf(stderr, "Cannot enable %s discovery component `%s' twice\n",
		hwloc_disc_component_type_string(backend->component->type), backend->component->name);
      hwloc_backend_disable(backend);
      errno = EBUSY;
      return -1;
    }
    pprev = &((*pprev)->next);
  }

  if (hwloc_components_verbose)
    fprintf(stderr, "Enabling %s discovery component `%s'\n",
	    hwloc_disc_component_type_string(backend->component->type), backend->component->name);


  pprev = &topology->backends;
  while (NULL != *pprev)
    pprev = &((*pprev)->next);
  backend->next = *pprev;
  *pprev = backend;

  backend->topology = topology;

  return 0;
}
