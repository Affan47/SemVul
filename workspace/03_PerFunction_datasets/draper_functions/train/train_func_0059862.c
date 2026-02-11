calc_class_mask(THD *thd, plugin_ref plugin, void *arg)
{
  st_mysql_audit *data= plugin_data(plugin, struct st_mysql_audit *);
  if ((data= plugin_data(plugin, struct st_mysql_audit *)))
    add_audit_mask((unsigned long *) arg, data->class_mask);
  return 0;
}
