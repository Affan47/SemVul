set_inverse_periods_global()
{ struct global *g;

  g = globals(inverse_periods_global);
  g->attr.arrayptr->sizes[0] = SDIM;
  g->attr.arrayptr->sizes[1] = SDIM;
  g->attr.arrayptr->datacount = SDIM*SDIM;
  g->attr.arrayptr->datastart =
        (char*)&web.inverse_periods[0][0] - (char*)(g->attr.arrayptr);
}
