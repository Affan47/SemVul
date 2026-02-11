emitInlineAsmEnd(const MCSubtargetInfo &StartInfo,
                                     const MCSubtargetInfo *EndInfo) const {


  const bool WasThumb = isThumb(StartInfo);
  if (!EndInfo || WasThumb != isThumb(*EndInfo)) {
    OutStreamer->EmitAssemblerFlag(WasThumb ? MCAF_Code16 : MCAF_Code32);
  }
}
