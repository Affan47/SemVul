StoreFlags(MCStreamer &Out) {
    EmitInstruction(Out, MCInstBuilder(X86::PUSHF32));
    OrigSPOffset -= 4;
  }
