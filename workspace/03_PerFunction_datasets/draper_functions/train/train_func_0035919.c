genie_voiding_assignation (NODE_T * p)
{
  NODE_T *dst = SUB (p);
  NODE_T *src = NEXT_NEXT (dst);
  MOID_T *src_mode = SUB_MOID (p);
  ADDR_T pop_sp = stack_pointer, pop_fp = FRAME_DNS (frame_pointer);
  A68_REF z;
  BOOL_T caution;
  PROP_T self;
  UNIT (&self) = genie_voiding_assignation;
  SOURCE (&self) = p;
  EXECUTE_UNIT (dst);
  POP_OBJECT (p, &z, A68_REF);
  caution = (BOOL_T) IS_IN_HEAP (&z);
  if (caution) {
  }
  CHECK_REF (p, z, MOID (p));
  FRAME_DNS (frame_pointer) = REF_SCOPE (&z);
  EXECUTE_UNIT (src);
  STACK_DNS (src, src_mode, REF_SCOPE (&z));
  FRAME_DNS (frame_pointer) = pop_fp;
  stack_pointer = pop_sp;
  if (HAS_ROWS (src_mode)) {
    genie_clone_stack (p, src_mode, &z, &z);
  } else {
    COPY_ALIGNED (ADDRESS (&z), STACK_TOP, MOID_SIZE (src_mode));
  }
  if (caution) {
  }
  return (self);
}
