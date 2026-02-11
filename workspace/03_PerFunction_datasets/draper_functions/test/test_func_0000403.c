writemaskRegisterEncodingFromString(const std::string &s,
                                                       uint8_t OpSize) {
  ENCODING("VK1WM",           ENCODING_WRITEMASK)
  ENCODING("VK2WM",           ENCODING_WRITEMASK)
  ENCODING("VK4WM",           ENCODING_WRITEMASK)
  ENCODING("VK8WM",           ENCODING_WRITEMASK)
  ENCODING("VK16WM",          ENCODING_WRITEMASK)
  ENCODING("VK32WM",          ENCODING_WRITEMASK)
  ENCODING("VK64WM",          ENCODING_WRITEMASK)
  errs() << "Unhandled mask register encoding " << s << "\n";
  llvm_unreachable("Unhandled mask register encoding");
}
