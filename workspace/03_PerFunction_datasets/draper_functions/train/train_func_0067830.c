emit_prolog()
{


   this->current_annotation = "clear r0.2";
   dst_reg r0(retype(brw_vec4_grf(0, 0), BRW_REGISTER_TYPE_UD));
   vec4_instruction *inst = emit(GS_OPCODE_SET_DWORD_2_IMMED, r0, 0u);
   inst->force_writemask_all = true;


   this->vertex_count = src_reg(this, glsl_type::uint_type);


   this->current_annotation = "initialize vertex_count";
   inst = emit(MOV(dst_reg(this->vertex_count), 0u));
   inst->force_writemask_all = true;

   if (c->control_data_header_size_bits > 0) {


      this->control_data_bits = src_reg(this, glsl_type::uint_type);


      if (c->control_data_header_size_bits <= 32) {
         this->current_annotation = "initialize control data bits";
         inst = emit(MOV(dst_reg(this->control_data_bits), 0u));
         inst->force_writemask_all = true;
      }
   }


   if (c->gp->program.Base.InputsRead & VARYING_BIT_PSIZ) {
      this->current_annotation = "swizzle gl_PointSize input";
      for (int vertex = 0; vertex < c->gp->program.VerticesIn; vertex++) {
         dst_reg dst(ATTR,
                     BRW_VARYING_SLOT_COUNT * vertex + VARYING_SLOT_PSIZ);
         dst.type = BRW_REGISTER_TYPE_F;
         src_reg src(dst);
         dst.writemask = WRITEMASK_X;
         src.swizzle = BRW_SWIZZLE_WWWW;
         inst = emit(MOV(dst, src));


         inst->force_writemask_all = true;
      }
   }

   this->current_annotation = NULL;
}
