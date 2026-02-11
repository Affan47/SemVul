_mesa_nop_vertex_program(struct gl_context *ctx, struct gl_vertex_program *prog)
{
   struct prog_instruction *inst;
   GLuint inputAttr;


   inst = _mesa_alloc_instructions(2);
   if (!inst) {
      _mesa_error(ctx, GL_OUT_OF_MEMORY, "_mesa_nop_vertex_program");
      return;
   }

   _mesa_init_instructions(inst, 2);

   inst[0].Opcode = OPCODE_MOV;
   inst[0].DstReg.File = PROGRAM_OUTPUT;
   inst[0].DstReg.Index = VARYING_SLOT_COL0;
   inst[0].SrcReg[0].File = PROGRAM_INPUT;
   if (prog->Base.InputsRead & VERT_BIT_COLOR0)
      inputAttr = VERT_ATTRIB_COLOR0;
   else
      inputAttr = VERT_ATTRIB_TEX0;
   inst[0].SrcReg[0].Index = inputAttr;

   inst[1].Opcode = OPCODE_END;

   _mesa_free_instructions(prog->Base.Instructions,
                           prog->Base.NumInstructions);

   prog->Base.Instructions = inst;
   prog->Base.NumInstructions = 2;
   prog->Base.InputsRead = BITFIELD64_BIT(inputAttr);
   prog->Base.OutputsWritten = BITFIELD64_BIT(VARYING_SLOT_COL0);


   _mesa_insert_mvp_code(ctx, prog);
}
