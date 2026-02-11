DoBinaryConstOpCpxReal(imcfloat *map1, float value, imcfloat *map, int count, int op)
{
  int i;

  switch(op)
  {
  case IM_BIN_ADD:
#ifdef _OPENMP
#pragma omp parallel for if (IM_OMP_MINCOUNT(count))
#endif
    for (i = 0; i < count; i++)
      map[i] = add_op(map1[i], value);
    break;
  case IM_BIN_SUB:
#ifdef _OPENMP
#pragma omp parallel for if (IM_OMP_MINCOUNT(count))
#endif
    for (i = 0; i < count; i++)
      map[i] = sub_op(map1[i], value);
    break;
  case IM_BIN_MUL:
#ifdef _OPENMP
#pragma omp parallel for if (IM_OMP_MINCOUNT(count))
#endif
    for (i = 0; i < count; i++)
      map[i] = mul_op(map1[i], value);
    break;
  case IM_BIN_DIV:
#ifdef _OPENMP
#pragma omp parallel for if (IM_OMP_MINCOUNT(count))
#endif
    for (i = 0; i < count; i++)
      map[i] = div_op(map1[i], (imcfloat)value);
    break;
  case IM_BIN_DIFF:
#ifdef _OPENMP
#pragma omp parallel for if (IM_OMP_MINCOUNT(count))
#endif
    for (i = 0; i < count; i++)
      map[i] = diff_op(map1[i], value);
    break;
  case IM_BIN_MIN:
#ifdef _OPENMP
#pragma omp parallel for if (IM_OMP_MINCOUNT(count))
#endif
    for (i = 0; i < count; i++)
      map[i] = min_op(map1[i], value);
    break;
  case IM_BIN_MAX:
#ifdef _OPENMP
#pragma omp parallel for if (IM_OMP_MINCOUNT(count))
#endif
    for (i = 0; i < count; i++)
      map[i] = max_op(map1[i], value);
    break;
  case IM_BIN_POW:
#ifdef _OPENMP
#pragma omp parallel for if (IM_OMP_MINCOUNT(count))
#endif
    for (i = 0; i < count; i++)
      map[i] = pow_op(map1[i], value);
    break;
  }
}
