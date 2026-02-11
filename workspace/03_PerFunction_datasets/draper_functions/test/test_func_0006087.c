eval_condition(const struct gl_program_machine *machine,
               const struct prog_instruction *inst)
{
   const GLuint swizzle = inst->DstReg.CondSwizzle;
   const GLuint condMask = inst->DstReg.CondMask;
   if (test_cc(machine->CondCodes[GET_SWZ(swizzle, 0)], condMask) ||
       test_cc(machine->CondCodes[GET_SWZ(swizzle, 1)], condMask) ||
       test_cc(machine->CondCodes[GET_SWZ(swizzle, 2)], condMask) ||
       test_cc(machine->CondCodes[GET_SWZ(swizzle, 3)], condMask)) {
      return GL_TRUE;
   }
   else {
      return GL_FALSE;
   }
}
