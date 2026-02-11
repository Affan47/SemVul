get_bitmap_visitor(struct st_fragment_program *fp,
                   glsl_to_tgsi_visitor *original, int samplerIndex)
{
   glsl_to_tgsi_visitor *v = new glsl_to_tgsi_visitor();
   struct st_context *st = st_context(original->ctx);
   struct gl_program *prog = &fp->Base.Base;
   st_src_reg coord, src0;
   st_dst_reg dst0;
   glsl_to_tgsi_instruction *inst;


   v->ctx = original->ctx;
   v->prog = prog;
   v->shader_program = NULL;
   v->glsl_version = original->glsl_version;
   v->native_integers = original->native_integers;
   v->options = original->options;
   v->next_temp = original->next_temp;
   v->num_address_regs = original->num_address_regs;
   v->samplers_used = prog->SamplersUsed = original->samplers_used;
   v->indirect_addr_consts = original->indirect_addr_consts;
   memcpy(&v->immediates, &original->immediates, sizeof(v->immediates));
   v->num_immediates = original->num_immediates;


   coord = st_src_reg(PROGRAM_INPUT, VARYING_SLOT_TEX0, glsl_type::vec2_type);
   src0 = v->get_temp(glsl_type::vec4_type);
   dst0 = st_dst_reg(src0);
   inst = v->emit(NULL, TGSI_OPCODE_TEX, dst0, coord);
   inst->sampler = samplerIndex;
   inst->tex_target = TEXTURE_2D_INDEX;

   prog->InputsRead |= VARYING_BIT_TEX0;
   prog->SamplersUsed |= (1 << samplerIndex);
   v->samplers_used |= (1 << samplerIndex);


   src0.negate = NEGATE_XYZW;
   if (st->bitmap.tex_format == PIPE_FORMAT_L8_UNORM)
      src0.swizzle = SWIZZLE_XXXX;
   inst = v->emit(NULL, TGSI_OPCODE_KILL_IF, undef_dst, src0);


   foreach_list(node, &original->instructions) {
      glsl_to_tgsi_instruction *inst = (glsl_to_tgsi_instruction *) node;
      glsl_to_tgsi_instruction *newinst;
      st_src_reg src_regs[3];

      if (inst->dst.file == PROGRAM_OUTPUT)
         prog->OutputsWritten |= BITFIELD64_BIT(inst->dst.index);

      for (int i=0; i<3; i++) {
         src_regs[i] = inst->src[i];
         if (src_regs[i].file == PROGRAM_INPUT)
            prog->InputsRead |= BITFIELD64_BIT(src_regs[i].index);
      }

      newinst = v->emit(NULL, inst->op, inst->dst, src_regs[0], src_regs[1], src_regs[2]);
      newinst->tex_target = inst->tex_target;
   }


   prog->Parameters = _mesa_clone_parameter_list(original->prog->Parameters);
   count_resources(v, prog);
   fp->glsl_to_tgsi = v;
}
