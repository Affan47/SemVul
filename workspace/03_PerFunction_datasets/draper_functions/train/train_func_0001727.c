Draw_Fractal (IfsData * data)
{
  FRACTAL *F = data->Root;
  int i, j;
  F_PT x, y, xo, yo;
  SIMI *Cur, *Simi;

  for (Cur = F->Components, i = F->Nb_Simi; i; --i, Cur++) {
    Cur->Cx = DBL_To_F_PT (Cur->c_x);
    Cur->Cy = DBL_To_F_PT (Cur->c_y);

    Cur->Ct = DBL_To_F_PT (cos (Cur->A));
    Cur->St = DBL_To_F_PT (sin (Cur->A));
    Cur->Ct2 = DBL_To_F_PT (cos (Cur->A2));
    Cur->St2 = DBL_To_F_PT (sin (Cur->A2));

    Cur->R = DBL_To_F_PT (Cur->r);
    Cur->R2 = DBL_To_F_PT (Cur->r2);
  }


  data->Cur_Pt = 0;
  data->Cur_F = F;
  data->Buf = F->Buffer2;
  for (Cur = F->Components, i = F->Nb_Simi; i; --i, Cur++) {
    xo = Cur->Cx;
    yo = Cur->Cy;
    for (Simi = F->Components, j = F->Nb_Simi; j; --j, Simi++) {
      if (Simi == Cur)
        continue;
      Transform (Simi, xo, yo, &x, &y);
      Trace (F, x, y, data);
    }
  }


  F->Cur_Pt = data->Cur_Pt;
  data->Buf = F->Buffer1;
  F->Buffer1 = F->Buffer2;
  F->Buffer2 = data->Buf;
}
