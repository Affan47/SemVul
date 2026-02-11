texture_lookup(struct brw_reg dst,
                                       enum opcode op,
                                       const sampler_message_arg *args,
                                       int num_args)
{
   struct brw_reg mrf =
      retype(vec16(brw_message_reg(base_mrf)), BRW_REGISTER_TYPE_UD);
   for (int arg = 0; arg < num_args; ++arg) {
      switch (args[arg]) {
      case SAMPLER_MESSAGE_ARG_U_FLOAT:
         if (key->bilinear_filter)
            emit_mov(retype(mrf, BRW_REGISTER_TYPE_F),
                     retype(X, BRW_REGISTER_TYPE_F));
         else
            emit_mov(retype(mrf, BRW_REGISTER_TYPE_F), X);
         break;
      case SAMPLER_MESSAGE_ARG_V_FLOAT:
         if (key->bilinear_filter)
            emit_mov(retype(mrf, BRW_REGISTER_TYPE_F),
                     retype(Y, BRW_REGISTER_TYPE_F));
         else
            emit_mov(retype(mrf, BRW_REGISTER_TYPE_F), Y);
         break;
      case SAMPLER_MESSAGE_ARG_U_INT:
         emit_mov(mrf, X);
         break;
      case SAMPLER_MESSAGE_ARG_V_INT:
         emit_mov(mrf, Y);
         break;
      case SAMPLER_MESSAGE_ARG_SI_INT:


         if (s_is_zero)
            emit_mov(mrf, brw_imm_ud(0));
         else
            emit_mov(mrf, S);
         break;
      case SAMPLER_MESSAGE_ARG_MCS_INT:
         switch (key->tex_layout) {
         case INTEL_MSAA_LAYOUT_CMS:
            emit_mov(mrf, mcs_data);
            break;
         case INTEL_MSAA_LAYOUT_IMS:


            break;
         default:


            assert (!"Unsupported layout for MCS data");
            break;
         }
         break;
      case SAMPLER_MESSAGE_ARG_ZERO_INT:
         emit_mov(mrf, brw_imm_ud(0));
         break;
      }
      mrf.nr += 2;
   }

   emit_texture_lookup(retype(dst, BRW_REGISTER_TYPE_UW) ,
                       op,
                       base_mrf,
                       mrf.nr - base_mrf );
}
