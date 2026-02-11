_GD_AlterScalar(DIRFILE* D, int alter_literal, gd_type_t type,
    void *lout, const void *lin, char **sout, int *iout, const char *sin,
    int iin, int calculated)
{
  int r = 0;
  int set_lout = 0;
  int error = 0;

  dtrace("%p, %i, %x, %p, %p, %p, %p, \"%s\", %i, %i", D, alter_literal, type,
      lout, lin, sout, iout, sin, iin, calculated);

  if (sin == NULL) {
    if (*sout != NULL) {
      if (alter_literal) {

        r = GD_AS_FREE_SCALAR | GD_AS_MODIFIED;
        *sout = NULL;
        set_lout = 1;
      } else {


        r = GD_AS_FREE_SCALAR | GD_AS_MODIFIED;
        if (!calculated)
          error = gd_get_constant(D, *sout, GD_INT64, lout);
        *sout = NULL;
      }
    } else if (alter_literal) {

      set_lout = 1;
    }

  } else if (sin[0] == '\0') {
    if (*sout == NULL && alter_literal) {

      set_lout = 1;
    }

  } else {


    r = GD_AS_FREE_SCALAR | GD_AS_NEED_RECALC | GD_AS_MODIFIED;
    *sout = strdup(sin);
    if (*sout == NULL)
      _GD_SetError(D, GD_E_ALLOC, 0, NULL, 0, NULL);
    *iout = iin;
  }

  if (!error && set_lout) {
    r |= GD_AS_MODIFIED;
    if (type == GD_INT64)
      *(int64_t *)lout = *(int64_t *)lin;
    else if (type == GD_COMPLEX128)
      memcpy(lout, lin, 2 * sizeof(double));
    else if (type == GD_FLOAT64)
      *(double *)lout = *(double *)lin;
    else if (type == GD_INT16)
      *(int16_t *)lout = *(int16_t *)lin;
    else if (type == GD_UINT16)
      *(uint16_t *)lout = *(uint16_t *)lin;
    else
      _GD_InternalError(D);
  }

  if (error)
    r |= GD_AS_ERROR;

  dreturn("%i", r);
  return r;
}
