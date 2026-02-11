chk_alc(rslt, lifetime)
struct val_loc *rslt;
nodeptr lifetime;
   {
   struct tmplftm tmplftm;

   if (rslt == NULL) {
      if (lifetime == NULL)
         rslt = &ignore;
      else {
         tmplftm.cur_status = InUse;
         tmplftm.lifetime = lifetime;
         rslt = tmp_loc(alc_tmp(1, &tmplftm));
         }
      }
   else if (rslt->loc_type == V_Temp)
      tmp_status[rslt->u.tmp] = InUse;
   return rslt;
   }
