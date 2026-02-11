pivot_compar(const void* par1, const void* par2) {
  const struct pivot_desc *p1 = *(struct pivot_desc**)par1,
                          *p2 = *(struct pivot_desc**)par2;


  if (p1->type < p2->type) return -1;
  if (p1->type > p2->type) return 1;

  return strcasecmp((char*)p1->name, (char*)p2->name);
}
