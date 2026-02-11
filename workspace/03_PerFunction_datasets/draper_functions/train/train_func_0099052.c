EmitFrames(bool usingCFI) {
  if (!getNumFrameInfos())
    return;

  if (EmitEHFrame)
    MCDwarfFrameEmitter::Emit(*this, usingCFI, true);

  if (EmitDebugFrame)
    MCDwarfFrameEmitter::Emit(*this, usingCFI, false);
}
