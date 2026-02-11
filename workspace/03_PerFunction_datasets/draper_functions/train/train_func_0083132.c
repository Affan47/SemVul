traverseweakvalue (global_State *g, Table *h) {
  Node *n, *limit = gnodelast(h);


  int hasclears = (h->sizearray > 0);
  for (n = gnode(h, 0); n < limit; n++) {
    checkdeadkey(n);
    if (ttisnil(gval(n)))
      removeentry(n);
    else {
      lua_assert(!ttisnil(gkey(n)));
      markvalue(g, gkey(n));
      if (!hasclears && iscleared(g, gval(n)))
        hasclears = 1;
    }
  }
  if (hasclears)
    linktable(h, &g->weak);
  else
    linktable(h, &g->grayagain);
}
