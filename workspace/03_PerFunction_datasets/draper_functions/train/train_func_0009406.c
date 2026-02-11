vl_hog_prepare_buffers (VlHog * self, vl_size width, vl_size height, vl_size cellSize)
{
  vl_size hogWidth = (width + cellSize/2) / cellSize ;
  vl_size hogHeight = (height + cellSize/2) / cellSize ;

  assert(width > 3) ;
  assert(height > 3) ;
  assert(hogWidth > 0) ;
  assert(hogHeight > 0) ;

  if (self->hog &&
      self->hogWidth == hogWidth &&
      self->hogHeight == hogHeight) {

    memset(self->hog, 0, sizeof(float) * hogWidth * hogHeight * self->numOrientations * 2) ;
    memset(self->hogNorm, 0, sizeof(float) * hogWidth * hogHeight) ;
    return ;
  }

  if (self->hog) {
    vl_free(self->hog) ;
    self->hog = NULL ;
  }

  if (self->hogNorm) {
    vl_free(self->hogNorm) ;
    self->hogNorm = NULL ;
  }

  self->hog = vl_calloc(hogWidth * hogHeight * self->numOrientations * 2, sizeof(float)) ;
  self->hogNorm = vl_calloc(hogWidth * hogHeight, sizeof(float)) ;
  self->hogWidth = hogWidth ;
  self->hogHeight = hogHeight ;
}
