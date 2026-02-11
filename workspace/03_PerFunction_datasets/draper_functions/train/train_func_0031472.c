removeInstance(TemplateInstance *handle)
{
    size_t bi = handle->hash % buckets.dim;
    TemplateInstances *instances = buckets[bi];
    for (size_t i = 0; i < instances->dim; i++)
    {
        TemplateInstance *ti = (*instances)[i];
        if (handle == ti)
        {   instances->remove(i);
            break;
        }
    }
    --numinstances;
}
