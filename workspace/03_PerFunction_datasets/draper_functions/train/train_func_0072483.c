arbitree()
{
  long i;
  node *newtip, *newfork;

  spp = ajAcdGetInt("spp");
  nonodes = spp * 2 - 1;
  maketip(&root, 1);
  maketip(&newtip, 2);
  maketriad(&newfork, spp + 1);
  add_at(root, newtip, newfork);
  for (i = 3; i <= spp; i++) {
    maketip(&newtip, i);
    maketriad(&newfork, spp + i - 1);
    add_at(nodep[spp + i - 3], newtip, newfork);
  }
}
