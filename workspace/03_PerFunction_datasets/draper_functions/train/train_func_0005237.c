EmitAdvanceLoc(MCStreamer &Streamer,
                                         uint64_t AddrDelta) {
  SmallString<256> Tmp;
  raw_svector_ostream OS(Tmp);
  MCDwarfFrameEmitter::EncodeAdvanceLoc(AddrDelta, OS);
  Streamer.EmitBytes(OS.str(), 0);
}
