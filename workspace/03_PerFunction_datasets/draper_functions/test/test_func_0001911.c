generate_tex(vec4_instruction *ir, struct brw_reg dst)
{
   int msg_type = 0;

   switch (ir->opcode) {
   case SHADER_OPCODE_TEX:
   case SHADER_OPCODE_TXL:
      if (ir->shadow_compare) {
         msg_type = GEN5_SAMPLER_MESSAGE_SAMPLE_LOD_COMPARE;
      } else {
         msg_type = GEN5_SAMPLER_MESSAGE_SAMPLE_LOD;
      }
      break;
   case SHADER_OPCODE_TXD:
      if (ir->shadow_compare) {
         msg_type = HSW_SAMPLER_MESSAGE_SAMPLE_DERIV_COMPARE;
      } else {
         msg_type = GEN5_SAMPLER_MESSAGE_SAMPLE_DERIVS;
      }
      break;
   case SHADER_OPCODE_TXF:
      msg_type = GEN5_SAMPLER_MESSAGE_SAMPLE_LD;
      break;
   case SHADER_OPCODE_TXF_CMS:
      msg_type = GEN7_SAMPLER_MESSAGE_SAMPLE_LD2DMS;
      break;
   case SHADER_OPCODE_TXF_MCS:
      msg_type = GEN7_SAMPLER_MESSAGE_SAMPLE_LD_MCS;
      break;
   case SHADER_OPCODE_TXS:
      msg_type = GEN5_SAMPLER_MESSAGE_SAMPLE_RESINFO;
      break;
   case SHADER_OPCODE_TG4:
      if (ir->shadow_compare) {
         msg_type = GEN7_SAMPLER_MESSAGE_SAMPLE_GATHER4_C;
      } else {
         msg_type = GEN7_SAMPLER_MESSAGE_SAMPLE_GATHER4;
      }
      break;
   case SHADER_OPCODE_TG4_OFFSET:
      if (ir->shadow_compare) {
         msg_type = GEN7_SAMPLER_MESSAGE_SAMPLE_GATHER4_PO_C;
      } else {
         msg_type = GEN7_SAMPLER_MESSAGE_SAMPLE_GATHER4_PO;
      }
      break;
   default:
      assert(!"should not get here: invalid VS texture opcode");
      break;
   }

   if (ir->header_present) {
      MOV_RAW(retype(brw_message_reg(ir->base_mrf), BRW_REGISTER_TYPE_UD),
              retype(brw_vec8_grf(0, 0), BRW_REGISTER_TYPE_UD));

      if (ir->texture_offset) {

         default_state.access_mode = BRW_ALIGN_1;
         MOV_RAW(retype(brw_vec1_reg(MRF, ir->base_mrf, 2),
                        BRW_REGISTER_TYPE_UD),
                 brw_imm_ud(ir->texture_offset));
         default_state.access_mode = BRW_ALIGN_16;
      }
   }

   uint32_t surf_index =
      prog_data->base.binding_table.texture_start + ir->sampler;

   gen8_instruction *inst = next_inst(BRW_OPCODE_SEND);
   gen8_set_dst(brw, inst, dst);
   gen8_set_src0(brw, inst, brw_message_reg(ir->base_mrf));
   gen8_set_sampler_message(brw, inst,
                            surf_index,
                            ir->sampler,
                            msg_type,
                            1,
                            ir->mlen,
                            ir->header_present,
                            BRW_SAMPLER_SIMD_MODE_SIMD4X2);

   mark_surface_used(surf_index);
}
