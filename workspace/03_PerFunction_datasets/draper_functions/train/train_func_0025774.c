parse_route_header(void)
{
  char* str;
  int column = -1;
  route_head* rte;

  rte = route_head_alloc();

  bind_fields(route_header);
  while ((str = csv_lineparse(NULL, "\t", "", column++))) {
    int field_no = header_fields[route_header][column];
    switch (field_no) {
    case 1:
      rte->rte_name = DUPSTR(str);
      break;
    case 5:
      rte->rte_url = DUPSTR(str);
      break;
    }
  }
  route_add_head(rte);
  current_rte = rte;
}
