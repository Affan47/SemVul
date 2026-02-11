defect_screw_dislocate(gdouble *s, gdouble *v, struct model_pak *model)
{
gdouble dz, r44, r55, x[3];
GSList *clist, *mlist;
struct mol_pak *mol;
struct core_pak *core;
struct shel_pak *shell;

g_assert(model != NULL);


r44 = s[21] - ((s[15]*s[15])/s[14]);


r55 = s[28] - ((s[16]*s[16])/s[14]);

printf("\nReduced elastic compliances: S44 = %f, S55 = %f\n", r44, r55);
if (r44 == r55)
  printf("Isotropic case...\n");

if (fabs(r44) < FRACTION_TOLERANCE || fabs(r55) < FRACTION_TOLERANCE)
  {
  printf("Bad compliance matrix.\n");
  return;
  }

for (mlist=model->moles ; mlist ; mlist=g_slist_next(mlist))
  {
  mol = mlist->data;

  ARR3SET(x, mol->centroid);

  dz = defect_anisotropic_1(x, r44, r55, v);

  for (clist=mol->cores ; clist ; clist=g_slist_next(clist))
    {
    core = clist->data;
    core->x[2] += dz;
    if (core->shell)
      {
      shell = core->shell;
      shell->x[2] += dz;
      }
    }
  }
}
