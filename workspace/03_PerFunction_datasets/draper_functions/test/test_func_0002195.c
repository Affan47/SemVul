concerns_inessential_worm(int pos, int what)
{
  UNUSED(pos);
  return DRAGON2(what).safety == INESSENTIAL
        || worm[what].inessential;
}
