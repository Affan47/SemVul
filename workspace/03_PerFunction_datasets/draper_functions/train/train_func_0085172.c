get_factory_for(const char *type)
{
    worker_factory_record_t *factory = &worker_factories[0];
    while (factory->name) {
        if (0 == strcmp(factory->name, type)) {
            return factory->fac;
        }

        factory++;
    }

    return NULL;
}
