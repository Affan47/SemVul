getutent_r_unknown (struct utmp *buffer, struct utmp **result)
{

  if (setutent_unknown ())
    return (*__libc_utmp_jump_table->getutent_r) (buffer, result);


  *result = NULL;
  return -1;
}
