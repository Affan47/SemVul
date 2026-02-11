map_to_llvmopcode(int opcode)
{
    switch (opcode) {
      default: llvm_unreachable("Unhandled Opcode.");
#define HANDLE_INST(num, opc, clas) case num: return LLVM##opc;
#include "llvm/IR/Instruction.def"
#undef HANDLE_INST
    }
}
