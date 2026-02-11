vgadd(char *hfile, char *vgname)
{
    HFILEID     f;
    int32       ref;
    int32       vg;

    f = Hopen(hfile, DFACC_ALL, 0);
    if (f == FAIL)
      {
          fprintf(stderr, "cannot open %s. \n", hfile);
          exit(0);
      }
    Vinitialize(f);
    vg = Vattach(f, -1, "w");
    if (vg == FAIL)
      {
          fprintf(stderr, "cannot attach vg\n");
          exit(0);
      }
    ref = VQueryref(vg);
    Vsetname(vg, vgname);
    Vdetach(vg);
    Vfinish(f);
    Hclose(f);
    fprintf(stderr, "%d\n", (int) ref);
    return (1);

}
