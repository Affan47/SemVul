lookup_component(char *x)
{
  R2G specimen;
  R2G *match;
  specimen.rafsi = x;
  match = (R2G *) bsearch(&specimen, r2g, Number(r2g), sizeof(R2G), compare_r2g);
  if (!match) {
    return "?";
  } else {
    return match->gismu;
  }
}
