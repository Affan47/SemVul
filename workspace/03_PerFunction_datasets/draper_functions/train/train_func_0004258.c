x87_arith_op( struct x86_function *p, struct x86_reg dst, struct x86_reg arg,
			  unsigned char dst0ub0,
			  unsigned char dst0ub1,
			  unsigned char arg0ub0,
			  unsigned char arg0ub1,
			  unsigned char argmem_noreg)
{
   assert(dst.file == file_x87);

   if (arg.file == file_x87) {
      if (dst.idx == 0)
	 emit_2ub(p, dst0ub0, dst0ub1+arg.idx);
      else if (arg.idx == 0)
	 emit_2ub(p, arg0ub0, arg0ub1+arg.idx);
      else
	 assert(0);
   }
   else if (dst.idx == 0) {
      assert(arg.file == file_REG32);
      emit_1ub(p, 0xd8);
      emit_modrm_noreg(p, argmem_noreg, arg);
   }
   else
      assert(0);
}
