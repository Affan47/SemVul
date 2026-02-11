process_mongroups()
{
 for (int i = 0; i < zg.size(); i++) {
  if (zg[i].dying) {
   zg[i].population *= .8;
   zg[i].radius *= .9;
  }
 }
}
