_energyFromImage(pullTask *task, pullPoint *point,

                 double egradSum[4]) {
  static const char me[]="_energyFromImage";
  double energy, grad3[3], _gamma;
  int probed;


  probed = AIR_FALSE;


#define MAYBEPROBE \
  if (!probed) { \
    if (pullProbe(task, point)) { \
      fprintf(stderr, "%s: problem probing!!!\n%s\n", me, biffGetDone(PULL)); \
    } \
    probed = AIR_TRUE; \
  }

  _gamma = task->pctx->sysParm.gamma;
  energy = 0;
  if (egradSum) {
    ELL_4V_SET(egradSum, 0, 0, 0, 0);
  }
  if (task->pctx->flag.energyFromStrength
      && task->pctx->ispec[pullInfoStrength]) {
    double deltaScale, str0, str1, scl0, scl1, enr;
    int sign;
    if (!egradSum) {

      MAYBEPROBE;
      enr = pullPointScalar(task->pctx, point, pullInfoStrength,
                            NULL, NULL);
      energy += -_gamma*enr;
    } else {


      sign = 2*AIR_CAST(int, airRandInt_r(task->rng, 2)) - 1;
      deltaScale = task->pctx->bboxMax[3] - task->pctx->bboxMin[3];
      deltaScale *= sign*_PULL_STRENGTH_ENERGY_DELTA_SCALE;
      scl1 = (point->pos[3] += deltaScale);
      pullProbe(task, point);
      str1 = pullPointScalar(task->pctx, point, pullInfoStrength,
                             NULL, NULL);
      scl0 = (point->pos[3] -= deltaScale);
      MAYBEPROBE;
      str0 = pullPointScalar(task->pctx, point, pullInfoStrength,
                             NULL, NULL);
      energy += -_gamma*str0;
      egradSum[3] += -_gamma*(str1 - str0)/(scl1 - scl0);


    }
  }


  if (task->pctx->ispec[pullInfoHeight]
      && !task->pctx->ispec[pullInfoHeight]->constraint
      && !(task->pctx->ispec[pullInfoHeightLaplacian]
           && task->pctx->ispec[pullInfoHeightLaplacian]->constraint)) {
    MAYBEPROBE;
    energy += pullPointScalar(task->pctx, point, pullInfoHeight,
                              grad3, NULL);
    if (egradSum) {
      ELL_3V_INCR(egradSum, grad3);
    }
  }
  if (task->pctx->ispec[pullInfoIsovalue]
      && !task->pctx->ispec[pullInfoIsovalue]->constraint) {


    double val;
    MAYBEPROBE;
    val = pullPointScalar(task->pctx, point, pullInfoIsovalue,
                          grad3, NULL);
    energy += val*val;
    if (egradSum) {
      ELL_3V_SCALE_INCR(egradSum, 2*val, grad3);
    }
  }
  return energy;
}
