echoIntxLightColor(echoCol_t ambi[3], echoCol_t diff[3], echoCol_t spec[3],
                   echoCol_t sp,
                   echoIntx *intx, echoScene *scene, echoRTParm *parm,
                   echoThreadState *tstate) {
  unsigned int Lidx;
  int blocked;
  echoRay shadRay;
  echoIntx shadIntx;
  echoPos_t Ldist, Ldir[3], Lpos[3], Ldot;
  echoCol_t Lcol[3], fracseen;

  if (parm->shadow) {

    shadRay.shadow = AIR_TRUE;
    ELL_3V_COPY(shadRay.from, intx->pos);


    shadRay.neer = 30*ECHO_EPSILON;
  }


  ELL_3V_COPY(ambi, scene->ambi);


  if (scene->envmap) {
    echoEnvmapLookup(diff, intx->norm, scene->envmap);
  } else {
    ELL_3V_SET(diff, 0, 0, 0);
  }


  if (spec) {
    ELL_3V_SET(spec, 0, 0, 0);
  }
  for (Lidx=0; Lidx<scene->lightArr->len; Lidx++) {
    echoLightPosition(Lpos, scene->light[Lidx], tstate);
    ELL_3V_SUB(Ldir, Lpos, intx->pos);
    ELL_3V_NORM(Ldir, Ldir, Ldist);
    Ldot = ELL_3V_DOT(Ldir, intx->norm);


    if (echoTypeRectangle == intx->obj->type) {
      Ldot = AIR_ABS(Ldot);
    }
    if (Ldot <= 0) {
      continue;


    }
    if (parm->shadow) {
      ELL_3V_COPY(shadRay.dir, Ldir);
      shadRay.faar = Ldist;
      if (echoRayIntx(&shadIntx, &shadRay, scene, parm, tstate)) {
        if (1.0 == parm->shadow) {


          continue;
        }
        blocked = AIR_TRUE;
      } else {
        blocked = AIR_FALSE;
      }
    } else {
      blocked = AIR_FALSE;
    }
    fracseen = AIR_CAST(echoCol_t, blocked ? 1.0 - parm->shadow : 1.0);
    echoLightColor(Lcol, Ldist, scene->light[Lidx], parm, tstate);
    ELL_3V_SCALE_INCR_TT(diff, echoCol_t, fracseen*Ldot, Lcol);
    if (spec) {
      Ldot = ELL_3V_DOT(Ldir, intx->refl);
      if (echoTypeRectangle == intx->obj->type) {
        Ldot = AIR_ABS(Ldot);
      }
      if (Ldot > 0) {
        Ldot = pow(Ldot, sp);
        ELL_3V_SCALE_INCR_TT(spec, echoCol_t, fracseen*Ldot, Lcol);
      }
    }
  }
  return;
}
