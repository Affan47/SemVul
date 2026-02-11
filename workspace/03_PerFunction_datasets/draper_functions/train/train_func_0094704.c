snmp_map_stats(struct ifstat_driver *driver, int nifaces, void *pdata) {
  struct snmp_driver_data *data = driver->data;
  struct ifsnmp *ifsnmp = data->ifsnmp;
  struct ifstat_list *ifs = pdata;
  struct ifstat_data *cur;
  int i, toobig = 0;

  if (!snmp_get_ifinfos(data->session, nifaces, S_BIN | S_BOUT |
			(data->num_ifnames ? S_NUMNAME : S_IFNAME),
			ifsnmp, &toobig))
    return 1;

  if (toobig)
    snmp_toobig(driver);

  for (i=0; i < nifaces; i++) {
    if (ifsnmp[i].flags & S_INVALID)
      continue;
    if (!(ifsnmp[i].flags & S_BIN && ifsnmp[i].flags & S_BOUT))
      continue;

    if ((cur = ifstat_get_interface(ifs, ifsnmp[i].name)) != NULL) {
      ifstat_set_interface_stats(cur, ifsnmp[i].bin, ifsnmp[i].bout);
      ifstat_set_interface_index(cur, ifsnmp[i].index);
    }
  }
  return 1;
}
