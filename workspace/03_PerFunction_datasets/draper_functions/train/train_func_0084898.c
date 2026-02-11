_echoIntxColorPhong(INTXCOLOR_ARGS) {
  echoCol_t ambi[3], diff[3], spec[3], ka, kd, ks, sp;

  ka = intx->obj->mat[echoMatterPhongKa];
  kd = intx->obj->mat[echoMatterPhongKd];
  ks = intx->obj->mat[echoMatterPhongKs];
  sp = intx->obj->mat[echoMatterPhongSp];

  echoIntxMaterialColor(rgba, intx, parm);
  ELL_3V_SET(spec, 0, 0, 0);
  echoIntxLightColor(ambi, diff, ks ? spec : NULL, sp,
                     intx, scene, parm, tstate);
  rgba[0] = rgba[0]*(ka*ambi[0] + kd*diff[0]) + ks*spec[0];
  rgba[1] = rgba[1]*(ka*ambi[1] + kd*diff[1]) + ks*spec[1];
  rgba[2] = rgba[2]*(ka*ambi[2] + kd*diff[2]) + ks*spec[2];
  return;
}
