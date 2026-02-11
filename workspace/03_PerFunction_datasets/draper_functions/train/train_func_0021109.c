hfs_calc_env(GSList *select, struct model_pak *model)
{
gboolean flag, primary;
gint i, imax[3];
gdouble r2, dx[3];
GSList *ilist, *list, *list2, *nlist;
struct image_pak *image;
struct core_pak *core, *copy, *test;


g_assert(model != NULL);


for (i=0 ; i<model->periodic ; i++)
  imax[i] = HFS_RMAX/model->pbc[i] + 1;

model->image_limit[0] = imax[0];
model->image_limit[1] = imax[0]+1;
model->image_limit[2] = imax[1];
model->image_limit[3] = imax[1]+1;
model->image_limit[4] = imax[2];
model->image_limit[5] = imax[2]+1;
space_make_images(CREATE, model);
coords_compute(model);


nlist = NULL;
for (list=model->cores ; list ; list=g_slist_next(list))
  {
  core = list->data;


  if (g_slist_find(select, core))
    primary = TRUE;
  else
    primary = FALSE;


  ilist = NULL;
  do
    {


    copy = dup_core(core);
    if (ilist)
      {

      image = ilist->data;
      ARR3ADD(copy->rx, image->rx);
      ilist = g_slist_next(ilist);
      }
    else
      ilist = model->images;


    ARR3SET(copy->x, copy->rx);


    vecmat(model->ilatmat,copy->x);
    ARR3ADD(copy->x, model->centroid);

    copy->primary = primary;


    flag = FALSE;
    for (list2=select ; list2 ; list2=g_slist_next(list2))
      {
      test = list2->data;

      ARR3SET(dx, test->rx);
      ARR3SUB(dx, copy->rx);
      r2 = VEC3MAGSQ(dx);
      if (r2 < HFS_RMAX*HFS_RMAX)
        {
        flag = TRUE;
        break;
        }
      }
    if (flag)
      nlist = g_slist_prepend(nlist, copy);
    }
  while (ilist);
  }


space_make_images(INITIAL, model);

#if DEBUG_HFS_CALC_ENV
printf("hfs_calc_env: %d cores\n", g_slist_length(nlist));
#endif

return(nlist);
}
