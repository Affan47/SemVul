_vl_svm_update_statistics (VlSvm *self)
{
  vl_size i, k ;
  double inner, p ;

  memset(&self->statistics, 0, sizeof(VlSvmStatistics)) ;

  self->statistics.regularizer = self->bias * self->bias ;
  for (i = 0; i < self->dimension; i++) {
    self->statistics.regularizer += self->model[i] * self->model[i] ;
  }
  self->statistics.regularizer *= self->lambda * 0.5 ;

  for (k = 0; k < self->numData ; k++) {
    p = (self->weights) ? self->weights[k] : 1.0 ;
    if (p <= 0) continue ;
    inner = self->innerProductFn(self->data, k, self->model) ;
    inner += self->bias * self->biasMultiplier ;
    self->scores[k] = inner ;
    self->statistics.loss += p * self->lossFn(inner, self->labels[k]) ;
    if (self->solver == VlSvmSolverSdca) {

      self->statistics.dualLoss -= p * self->conjugateLossFn(- self->alpha[k] / p, self->labels[k]) ;
    }
  }

  self->statistics.loss /= self->numData ;
  self->statistics.objective = self->statistics.regularizer + self->statistics.loss ;

  if (self->solver == VlSvmSolverSdca) {
    self->statistics.dualLoss /= self->numData ;
    self->statistics.dualObjective = - self->statistics.regularizer + self->statistics.dualLoss ;
    self->statistics.dualityGap = self->statistics.objective - self->statistics.dualObjective ;
  }
}
