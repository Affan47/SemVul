nmn4_write_waypt(const waypoint* wpt)
{
  char city[128], street[128], zipc[32], number[32];

  if (curr_rte_num != target_rte_num) {
    return;
  }

  strncpy(city, "-", sizeof(city));
  strncpy(street, "-", sizeof(street));
  strncpy(zipc, "-", sizeof(zipc));
  strncpy(number, "-", sizeof(number));


  gbfprintf(fout, "-|-|-|-|%s|%s|%s|%s|%s|-|-|%.5f|%.5f|-|-|\r\n",
            zipc, city, zipc, street, number,
            wpt->longitude, wpt->latitude);
}
