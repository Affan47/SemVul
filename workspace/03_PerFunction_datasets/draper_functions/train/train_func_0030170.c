complete_mode (struct mode_data *m)
{
  unsigned int alignment;

  if (!m->name)
    {
      error ("%s:%d: mode with no name", m->file, m->line);
      return;
    }
  if (m->class == MAX_MODE_CLASS)
    {
      error ("%s:%d: %smode has no mode class", m->file, m->line, m->name);
      return;
    }

  switch (m->class)
    {
    case MODE_RANDOM:

      if (!strcmp (m->name, "VOID"))
	void_mode = m;

      validate_mode (m, UNSET, UNSET, UNSET, UNSET, UNSET);

      m->precision = 0;
      m->bytesize = 0;
      m->ncomponents = 0;
      m->component = 0;
      break;

    case MODE_CC:


      validate_mode (m, UNSET, UNSET, UNSET, UNSET, UNSET);

      m->bytesize = 4;
      m->ncomponents = 1;
      m->component = 0;
      break;

    case MODE_INT:
    case MODE_FLOAT:


      validate_mode (m, OPTIONAL, SET, UNSET, UNSET,
		     m->class == MODE_FLOAT ? SET : UNSET);

      m->ncomponents = 1;
      m->component = 0;
      break;

    case MODE_PARTIAL_INT:


      validate_mode (m, OPTIONAL, UNSET, SET, UNSET, UNSET);

      m->bytesize = m->component->bytesize;

      m->ncomponents = 1;
      m->component = 0;
      break;

    case MODE_COMPLEX_INT:
    case MODE_COMPLEX_FLOAT:

      validate_mode (m, UNSET, UNSET, SET, UNSET, UNSET);
      m->ncomponents = 2;
      if (m->component->precision != (unsigned int)-1)
	m->precision = 2 * m->component->precision;
      m->bytesize = 2 * m->component->bytesize;
      break;

    case MODE_VECTOR_INT:
    case MODE_VECTOR_FLOAT:

      validate_mode (m, UNSET, UNSET, SET, SET, UNSET);
      if (m->component->precision != (unsigned int)-1)
	m->precision = m->ncomponents * m->component->precision;
      m->bytesize = m->ncomponents * m->component->bytesize;
      break;

    default:
      abort ();
    }


  if (m->class == MODE_COMPLEX_INT || m->class == MODE_COMPLEX_FLOAT)
    alignment = m->component->bytesize;
  else
    alignment = m->bytesize;

  m->alignment = alignment & (~alignment + 1);


  if (m->component)
    {
      m->next_cont = m->component->contained;
      m->component->contained = m;
    }
}
