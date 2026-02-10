getDbgValue(MDNode *MDPtr, const Value *C, uint64_t Off,
                          DebugLoc DL, unsigned O) {
  return new (Allocator) SDDbgValue(MDPtr, C, Off, DL, O);
}
