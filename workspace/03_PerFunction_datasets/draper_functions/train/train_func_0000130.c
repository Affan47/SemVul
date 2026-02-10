get_table(const string &name)
{
    if (d_container) {
        return d_container->get_attr_table(name);
    }
    return d_attrs.get_attr_table(name);
}
