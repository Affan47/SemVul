InstBoundSphere(Inst *inst,
		      Transform T, TransformN *TN, int *axes, int space)
{
  Sphere *geomsphere, *sphere;
  Transform Tnew;
  GeomIter *it;

  if (inst == NULL || inst->geom == NULL)
    return NULL;

  if (inst->location > L_LOCAL || inst->origin > L_LOCAL)
    return NULL;

  if (T == NULL)
    T = TM_IDENTITY;

  if (inst->NDaxis == NULL) {
    if (TN == NULL) {
      it = GeomIterate((Geom *)inst, DEEP);
      geomsphere = NULL;
      while (NextTransform(it, Tnew) > 0) {
	TmConcat(Tnew, T, Tnew);
	sphere = (Sphere *)GeomBoundSphere(inst->geom, Tnew, NULL, NULL, space);
	if (sphere != NULL) {
	  if (geomsphere != NULL) {
	    SphereUnion3(geomsphere, sphere, geomsphere);
	    GeomDelete((Geom *)sphere);
	  } else geomsphere = sphere;
	}
      }
    } else {
      TransformN *TnewN = TmNCopy(TN, NULL);
      static int dflt_axes[] = { 1, 2, 3, 0 };

      it = GeomIterate((Geom *)inst, DEEP);
      geomsphere = NULL;
      while (NextTransform(it, Tnew) > 0) {


	TmNCopy(TN, TnewN);
	TmNApplyT3TN(Tnew, dflt_axes, TnewN);
	sphere =
	  (Sphere *)GeomBoundSphere(inst->geom, NULL, TnewN,  axes, space);
	if (sphere != NULL) {
	  if (geomsphere != NULL) {
	    SphereUnion3(geomsphere, sphere, geomsphere);
	    GeomDelete((Geom *)sphere);
	  } else geomsphere = sphere;
	}
      }

      TmNDelete(TnewN);
    }
  } else {
    if (TN) {
      TransformN *TnewN;

      TnewN = TmNConcat(inst->NDaxis, TN, NULL);
      geomsphere =
	(Sphere *)GeomBoundSphere(inst->geom, NULL, TnewN, axes, space);
      TmNDelete(TnewN);
    } else {
      TransformN *TnewN = TmNCopy(inst->NDaxis, NULL);
      static int dflt_axes[] = { 1, 2, 3, 0 };

      TmNApplyDN(TnewN, dflt_axes, T);
      geomsphere =
	(Sphere *)GeomBoundSphere(inst->geom, NULL, TnewN, dflt_axes, space);
      TmNDelete(TnewN);
    }
  }

  return (Geom *)geomsphere;
}
