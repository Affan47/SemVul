splotScreenToTform (cpaneld * cpanel, splotd * sp, icoords * scr,
                    fcoords * tfd, ggobid * gg)
{
  gcoords planar, world;
  greal precis = (greal) PRECISION1;
  greal ftmp, max, min, rdiff;
  displayd *display = (displayd *) sp->displayptr;
  GGobiData *d = display->d;
  gfloat scale_x, scale_y;
  vartabled *vt;

  scale_x = sp->scale.x;
  scale_y = sp->scale.y;
  scale_x /= 2;
  sp->iscale.x = (greal) sp->max.x * scale_x;
  scale_y /= 2;
  sp->iscale.y = -1 * (greal) sp->max.y * scale_y;


  planar.x = (scr->x - sp->max.x / 2) * precis / sp->iscale.x;
  planar.x += sp->pmid.x;
  planar.y = (scr->y - sp->max.y / 2) * precis / sp->iscale.y;
  planar.y += sp->pmid.y;


  if (sp->p1dvar != -1) {

    vt = vartable_element_get (sp->p1dvar, d);
    max = vt->lim.max;
    min = vt->lim.min;
    rdiff = max - min;

    if (display->p1d_orientation == HORIZONTAL) {

      world.x = planar.x;
      ftmp = world.x / precis;
      tfd->x = (ftmp + 1.0) * .5 * rdiff;
      tfd->x += min;
    }
    else {

      world.y = planar.y;
      ftmp = world.y / precis;
      tfd->y = (ftmp + 1.0) * .5 * rdiff;
      tfd->y += min;
    }
  }

}
