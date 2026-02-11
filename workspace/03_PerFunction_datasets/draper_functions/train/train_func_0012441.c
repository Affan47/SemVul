dmalloc_verify_pnt(const char *file, const int line, const char *func,
			   const void *pnt, const int exact_b,
			   const int min_size)
{
  if (min_size < 0) {
    return dmalloc_verify_pnt_strsize(file, line, func, pnt, exact_b,
				      1 , 0 );
  } else {
    return dmalloc_verify_pnt_strsize(file, line, func, pnt, exact_b,
				      0 , min_size);
  }
}
