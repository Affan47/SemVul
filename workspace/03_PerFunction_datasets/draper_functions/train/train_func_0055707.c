constraintSatIso(pullTask *task, pullPoint *point,
                 double stepMax, double constrEps,
                 unsigned int iterMax,

                 int *constrFailP) {
  static const char me[]="constraintSatIso";
  double
    step,
    val, aval,
    hack,

    grad[4], dir[3], len, state[1 + 1 + 3 + 3];
  unsigned int iter = 0;

  PROBE(val, aval, grad);
  SAVE(state, aval, val, grad, point->pos);
  hack = 1;
  for (iter=1; iter<=iterMax; iter++) {

    NORMALIZE(dir, grad, len);
    if (!len) {

      hack *= task->pctx->sysParm.backStepScale;
      RESTORE(aval, val, grad, point->pos, state);
      continue;
    }
    step = -val/len;
    step = step > 0 ? AIR_MIN(stepMax, step) : AIR_MAX(-stepMax, step);
    ELL_3V_SCALE_INCR(point->pos, hack*step, dir);
    PROBE(val, aval, grad);
    _pullPointHistAdd(point, pullCondConstraintSatA, val);
    if (aval <= state[0]) {
      if (AIR_ABS(step) < stepMax*constrEps) {

        break;
      }
      SAVE(state, aval, val, grad, point->pos);
      hack = 1;
    } else {
      hack *= task->pctx->sysParm.backStepScale;
      RESTORE(aval, val, grad, point->pos, state);
    }
  }
  if (iter > iterMax) {
    *constrFailP = pullConstraintFailIterMaxed;
  } else {
    *constrFailP = AIR_FALSE;
  }
  return 0;
}
