handleRDSV(Instruction *i)
{
   Symbol *sym = i->getSrc(0)->asSym();
   const SVSemantic sv = sym->reg.data.sv.sv;
   Value *vtx = NULL;
   Instruction *ld;
   uint32_t addr = targ->getSVAddress(FILE_SHADER_INPUT, sym);

   if (addr >= 0x400) {

      if (sym->reg.data.sv.index == 3) {

         i->op = OP_MOV;
         i->setSrc(0, bld.mkImm((sv == SV_NTID || sv == SV_NCTAID) ? 1 : 0));
      }
      return true;
   }

   switch (sv) {
   case SV_POSITION:
      assert(prog->getType() == Program::TYPE_FRAGMENT);
      bld.mkInterp(NV50_IR_INTERP_LINEAR, i->getDef(0), addr, NULL);
      break;
   case SV_FACE:
   {
      Value *face = i->getDef(0);
      bld.mkInterp(NV50_IR_INTERP_FLAT, face, addr, NULL);
      if (i->dType == TYPE_F32) {
         bld.mkOp2(OP_AND, TYPE_U32, face, face, bld.mkImm(0x80000000));
         bld.mkOp2(OP_XOR, TYPE_U32, face, face, bld.mkImm(0xbf800000));
      }
   }
      break;
   case SV_TESS_COORD:
      assert(prog->getType() == Program::TYPE_TESSELLATION_EVAL);
      readTessCoord(i->getDef(0)->asLValue(), i->getSrc(0)->reg.data.sv.index);
      break;
   case SV_NTID:
   case SV_NCTAID:
   case SV_GRIDID:
      assert(targ->getChipset() >= NVISA_GK104_CHIPSET);
      if (sym->reg.data.sv.index == 3) {
         i->op = OP_MOV;
         i->setSrc(0, bld.mkImm(sv == SV_GRIDID ? 0 : 1));
         return true;
      }
      addr += prog->driver->prop.cp.gridInfoBase;
      bld.mkLoad(TYPE_U32, i->getDef(0),
                 bld.mkSymbol(FILE_MEMORY_CONST, 0, TYPE_U32, addr), NULL);
      break;
   default:
      if (prog->getType() == Program::TYPE_TESSELLATION_EVAL)
         vtx = bld.mkOp1v(OP_PFETCH, TYPE_U32, bld.getSSA(), bld.mkImm(0));
      ld = bld.mkFetch(i->getDef(0), i->dType,
                       FILE_SHADER_INPUT, addr, i->getIndirect(0, 0), vtx);
      ld->perPatch = i->perPatch;
      break;
   }
   bld.getBB()->remove(i);
   return true;
}
