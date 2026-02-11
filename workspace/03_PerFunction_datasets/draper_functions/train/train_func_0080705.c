id_matches_type(unsigned long id, const ioctl_type *type)
{
    return _IOC_TYPE(id) == _IOC_TYPE(type->id) &&
           _IOC_DIR(id) == _IOC_DIR(type->id) &&
           _IOC_NR(id) >= _IOC_NR(type->id) &&
           _IOC_NR(id) <= _IOC_NR(type->id) + type->nr_range;
}
