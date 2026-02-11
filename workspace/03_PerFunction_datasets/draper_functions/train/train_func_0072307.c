make_vector_modes (enum mode_class cl, unsigned int width,
		   const char *file, unsigned int line)
{
  struct mode_data *m;
  struct mode_data *v;
  char buf[8];
  unsigned int ncomponents;
  enum mode_class vclass = vector_class (cl);

  if (vclass == MODE_RANDOM)
    return;

  for (m = modes[cl]; m; m = m->next)
    {


      ncomponents = width / m->bytesize;
      if (ncomponents < 2)
	continue;
      if (width % m->bytesize)
	continue;


      if (cl == MODE_FLOAT && m->bytesize == 1)
	continue;
      if (cl == MODE_INT && m->precision == 1)
	continue;

      if ((size_t)snprintf (buf, sizeof buf, "V%u%s", ncomponents, m->name)
	  >= sizeof buf)
	{
	  error ("%s:%d: mode name \"%s\" is too long",
		 m->file, m->line, m->name);
	  continue;
	}

      v = new_mode (vclass, xstrdup (buf), file, line);
      v->component = m;
      v->ncomponents = ncomponents;
    }
}
