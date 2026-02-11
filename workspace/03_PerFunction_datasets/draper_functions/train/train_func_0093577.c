deregisterEHFrames() {
  for (int i = 0, e = RegisteredEHFrameSections.size(); i != e; ++i) {
    SID EHFrameSID = RegisteredEHFrameSections[i];
    uint8_t *EHFrameAddr = Sections[EHFrameSID].Address;
    uint64_t EHFrameLoadAddr = Sections[EHFrameSID].LoadAddress;
    size_t EHFrameSize = Sections[EHFrameSID].Size;
    MemMgr.deregisterEHFrames(EHFrameAddr, EHFrameLoadAddr, EHFrameSize);
  }
  RegisteredEHFrameSections.clear();
}
