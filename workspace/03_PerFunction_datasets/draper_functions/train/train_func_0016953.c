osc_collect_arguments(const char *dsc, const u8 *p, osc_data_t *data)
{
  dsc++;
  i32 i = 0;
  while(*dsc != '\0') {
    u8 c = *dsc;
    if(c == 'i') {
      data[i].i = ntoh_i32_from_buf(p);
      p += 4;
    } else if(c == 'h') {
      data[i].h = ntoh_i64_from_buf(p);
      p += 8;
    } else if(c == 't') {
      data[i].t = ntoh_u64_from_buf(p);
      p += 8;
    } else if(c == 'f') {
      data[i].f = ntoh_f32_from_buf(p);
      p += 4;
    } else if(c == 'd') {
      data[i].d = ntoh_f64_from_buf(p);
      p += 8;
    } else if(c == 's') {
      data[i].s = (char*)p;
      p += osc_str_bound(u8strlen(p));
    } else if(c == 'S') {
      data[i].S = (char*)p;
      p += osc_str_bound(u8strlen(p));
    } else if(c == 'c') {
      data[i].c = ntoh_u32_from_buf(p);
      p += 4;
    } else if(c == 'm') {
      data[i].m = ntoh_u32_from_buf(p);
      p += 4;
    } else if(c == 'r') {
      data[i].r = ntoh_u32_from_buf(p);
      p += 4;
    } else if(c == 'b') {
      data[i].b.data = p + 4;
      data[i].b.size = ntoh_i32_from_buf(p);
      p += data[i].b.size + 4;
    } else {
      return -1;
    }
    dsc++;
    i++;
  }
  return 0;
}
