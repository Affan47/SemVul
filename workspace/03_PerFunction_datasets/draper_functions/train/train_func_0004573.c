push_mode (FILE_T f, MOID_T * m)
{
  (void) f;
  if (_m_sp < STACK_SIZE) {
    _m_stack[_m_sp++] = m;
  } else {
    monitor_error ("expression too complex", NO_TEXT);
  }
}
