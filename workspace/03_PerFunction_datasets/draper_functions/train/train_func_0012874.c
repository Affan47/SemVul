ShowKernelInfo(const KernelInfo *kernel)
{
  const KernelInfo
    *k;

  size_t
    c, i, u, v;

  for (c=0, k=kernel;  k != (KernelInfo *) NULL;  c++, k=k->next ) {

    (void) FormatLocaleFile(stderr, "Kernel");
    if ( kernel->next != (KernelInfo *) NULL )
      (void) FormatLocaleFile(stderr, " #%lu", (unsigned long) c );
    (void) FormatLocaleFile(stderr, " \"%s",
          CommandOptionToMnemonic(MagickKernelOptions, k->type) );
    if ( fabs(k->angle) >= MagickEpsilon )
      (void) FormatLocaleFile(stderr, "@%lg", k->angle);
    (void) FormatLocaleFile(stderr, "\" of size %lux%lu%+ld%+ld",(unsigned long)
      k->width,(unsigned long) k->height,(long) k->x,(long) k->y);
    (void) FormatLocaleFile(stderr,
          " with values from %.*lg to %.*lg\n",
          GetMagickPrecision(), k->minimum,
          GetMagickPrecision(), k->maximum);
    (void) FormatLocaleFile(stderr, "Forming a output range from %.*lg to %.*lg",
          GetMagickPrecision(), k->negative_range,
          GetMagickPrecision(), k->positive_range);
    if ( fabs(k->positive_range+k->negative_range) < MagickEpsilon )
      (void) FormatLocaleFile(stderr, " (Zero-Summing)\n");
    else if ( fabs(k->positive_range+k->negative_range-1.0) < MagickEpsilon )
      (void) FormatLocaleFile(stderr, " (Normalized)\n");
    else
      (void) FormatLocaleFile(stderr, " (Sum %.*lg)\n",
          GetMagickPrecision(), k->positive_range+k->negative_range);
    for (i=v=0; v < k->height; v++) {
      (void) FormatLocaleFile(stderr, "%2lu:", (unsigned long) v );
      for (u=0; u < k->width; u++, i++)
        if ( IsNan(k->values[i]) )
          (void) FormatLocaleFile(stderr," %*s", GetMagickPrecision()+3, "nan");
        else
          (void) FormatLocaleFile(stderr," %*.*lg", GetMagickPrecision()+3,
              GetMagickPrecision(), k->values[i]);
      (void) FormatLocaleFile(stderr,"\n");
    }
  }
}
