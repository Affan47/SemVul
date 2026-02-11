ScaleKernelInfo(KernelInfo *kernel,
  const double scaling_factor,const GeometryFlags normalize_flags)
{
  register ssize_t
    i;

  register double
    pos_scale,
    neg_scale;


  if ( kernel->next != (KernelInfo *) NULL)
    ScaleKernelInfo(kernel->next, scaling_factor, normalize_flags);


  pos_scale = 1.0;
  if ( (normalize_flags&NormalizeValue) != 0 ) {
    if ( fabs(kernel->positive_range + kernel->negative_range) >= MagickEpsilon )

      pos_scale = fabs(kernel->positive_range + kernel->negative_range);
    else

      pos_scale = kernel->positive_range;
  }

  if ( (normalize_flags&CorrelateNormalizeValue) != 0 ) {
    pos_scale = ( fabs(kernel->positive_range) >= MagickEpsilon )
                 ? kernel->positive_range : 1.0;
    neg_scale = ( fabs(kernel->negative_range) >= MagickEpsilon )
                 ? -kernel->negative_range : 1.0;
  }
  else
    neg_scale = pos_scale;


  pos_scale = scaling_factor/pos_scale;
  neg_scale = scaling_factor/neg_scale;

  for (i=0; i < (ssize_t) (kernel->width*kernel->height); i++)
    if ( ! IsNan(kernel->values[i]) )
      kernel->values[i] *= (kernel->values[i] >= 0) ? pos_scale : neg_scale;


  kernel->positive_range *= pos_scale;
  kernel->negative_range *= neg_scale;

  kernel->maximum *= (kernel->maximum >= 0.0) ? pos_scale : neg_scale;
  kernel->minimum *= (kernel->minimum >= 0.0) ? pos_scale : neg_scale;


  if ( scaling_factor < MagickEpsilon ) {
    double t;
    t = kernel->positive_range;
    kernel->positive_range = kernel->negative_range;
    kernel->negative_range = t;
    t = kernel->maximum;
    kernel->maximum = kernel->minimum;
    kernel->minimum = 1;
  }

  return;
}
