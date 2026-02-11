emit(ir_instruction *ir, unsigned op,
        		 st_dst_reg dst, st_src_reg src0)
{
   assert(dst.writemask != 0);
   return emit(ir, op, dst, src0, undef_src, undef_src);
}
