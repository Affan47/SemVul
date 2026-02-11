genie_identifier (NODE_T * p)
{
  static PROP_T self;
  TAG_T *q = TAX (p);
  SOURCE (&self) = p;
  if (A68G_STANDENV_PROC (q)) {
    if (IS (MOID (q), PROC_SYMBOL)) {
      (void) genie_identifier_standenv_proc (p);
      UNIT (&self) = genie_identifier_standenv_proc;
    } else {
      (void) genie_identifier_standenv (p);
      UNIT (&self) = genie_identifier_standenv;
    }
  } else if (STATUS_TEST (q, CONSTANT_MASK)) {
    int size = MOID_SIZE (MOID (p));
    BYTE_T *sp_0 = STACK_TOP;
    (void) genie_frame_identifier (p);
    CONSTANT (GINFO (p)) = (void *) get_heap_space ((size_t) size);
    SIZE (GINFO (p)) = size;
    COPY (CONSTANT (GINFO (p)), (void *) sp_0, size);
    UNIT (&self) = genie_constant;
  } else {
    (void) genie_frame_identifier (p);
    UNIT (&self) = genie_frame_identifier;
  }
  return (self);
}
