EmitFrames(MCAsmBackend *MAB) {
  if (!getNumFrameInfos())
    return;

  if (EmitEHFrame)
    MCDwarfFrameEmitter::Emit(*this, MAB, true);

  if (EmitDebugFrame)
    MCDwarfFrameEmitter::Emit(*this, MAB, false);
}
