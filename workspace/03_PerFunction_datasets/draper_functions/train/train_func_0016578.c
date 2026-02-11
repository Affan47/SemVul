max_inner (pIIR_DeclarativeRegion r1, pIIR_DeclarativeRegion r2, RegionStack &rstack)
{


  for (pIIR_DeclarativeRegion r = r1; r != NULL; r = get_parent_declarative_region(r, rstack)) {

    if (r == r2)
      return r1;
  }
  return r2;
}
