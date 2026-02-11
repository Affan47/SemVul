compute_frag_coords()
{


   emit_add(vec16(retype(X, BRW_REGISTER_TYPE_UW)),
           stride(suboffset(R1, 4), 2, 4, 0), brw_imm_v(0x10101010));


   emit_add(vec16(retype(Y, BRW_REGISTER_TYPE_UW)),
           stride(suboffset(R1, 5), 2, 4, 0), brw_imm_v(0x11001100));


   emit_mov(vec16(Xp), retype(X, BRW_REGISTER_TYPE_UW));
   emit_mov(vec16(Yp), retype(Y, BRW_REGISTER_TYPE_UW));
   SWAP_XY_AND_XPYP();

   if (key->persample_msaa_dispatch) {
      switch (key->rt_samples) {
      case 4: {


         struct brw_reg t1_uw1 = retype(t1, BRW_REGISTER_TYPE_UW);
         emit_mov(vec16(t1_uw1), brw_imm_v(0x3210));

         emit_mov_8(S, stride(t1_uw1, 1, 4, 0));
         emit_mov_8(offset(S, 1), suboffset(stride(t1_uw1, 1, 4, 0), 2));
         break;
      }
      case 8: {


         struct brw_reg t1_ud1 = vec1(retype(t1, BRW_REGISTER_TYPE_UD));
         struct brw_reg t2_uw1 = retype(t2, BRW_REGISTER_TYPE_UW);
         struct brw_reg r0_ud1 = vec1(retype(R0, BRW_REGISTER_TYPE_UD));
         emit_and(t1_ud1, r0_ud1, brw_imm_ud(0xc0));
         emit_shr(t1_ud1, t1_ud1, brw_imm_ud(5));
         emit_mov(vec16(t2_uw1), brw_imm_v(0x3210));
         emit_add(vec16(S), retype(t1_ud1, BRW_REGISTER_TYPE_UW),
                  stride(t2_uw1, 1, 4, 0));
         emit_add_8(offset(S, 1),
                    retype(t1_ud1, BRW_REGISTER_TYPE_UW),
                    suboffset(stride(t2_uw1, 1, 4, 0), 2));
         break;
      }
      default:
         assert(!"Unrecognized sample count in "
                "brw_blorp_blit_program::compute_frag_coords()");
         break;
      }
      s_is_zero = false;
   } else {


      s_is_zero = true;
   }
}
