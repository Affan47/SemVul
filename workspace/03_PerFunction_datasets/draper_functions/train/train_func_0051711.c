vl_covdet_append_feature (VlCovDet * self, VlCovDetFeature const * feature)
{
  vl_size requiredSize ;
  assert(self) ;
  assert(feature) ;
  self->numFeatures ++ ;
  requiredSize = self->numFeatures * sizeof(VlCovDetFeature) ;
  if (requiredSize > self->numFeatureBufferSize) {
    int err = _vl_resize_buffer((void**)&self->features, &self->numFeatureBufferSize,
                                (self->numFeatures + 1000) * sizeof(VlCovDetFeature)) ;
    if (err) {
      self->numFeatures -- ;
      return err ;
    }
  }
  self->features[self->numFeatures - 1] = *feature ;
  return VL_ERR_OK ;
}
