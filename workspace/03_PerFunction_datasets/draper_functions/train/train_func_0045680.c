brw_copy_from_indirect(struct brw_compile *p,
			    struct brw_reg dst,
			    struct brw_indirect ptr,
			    unsigned count)
{
   unsigned i;

   dst = vec4(dst);

   for (i = 0; i < count; i++)
   {
      unsigned delta = i*32;
      brw_MOV(p, byte_offset(dst, delta),    deref_4f(ptr, delta));
      brw_MOV(p, byte_offset(dst, delta+16), deref_4f(ptr, delta+16));
   }
}
