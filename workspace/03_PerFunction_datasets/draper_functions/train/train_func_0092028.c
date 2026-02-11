immediateEncodingFromString(const std::string &s,
                                               uint8_t OpSize) {
  if(OpSize != X86Local::OpSize16) {


    ENCODING("i16imm",        ENCODING_IW)
  }
  ENCODING("i32i8imm",        ENCODING_IB)
  ENCODING("SSECC",           ENCODING_IB)
  ENCODING("XOPCC",           ENCODING_IB)
  ENCODING("AVXCC",           ENCODING_IB)
  ENCODING("AVX512ICC",       ENCODING_IB)
  ENCODING("AVX512RC",        ENCODING_IB)
  ENCODING("i16imm",          ENCODING_Iv)
  ENCODING("i16i8imm",        ENCODING_IB)
  ENCODING("i32imm",          ENCODING_Iv)
  ENCODING("i64i32imm",       ENCODING_ID)
  ENCODING("i64i8imm",        ENCODING_IB)
  ENCODING("i8imm",           ENCODING_IB)
  ENCODING("u8imm",           ENCODING_IB)
  ENCODING("i32u8imm",        ENCODING_IB)


  ENCODING("FR32",            ENCODING_IB)
  ENCODING("FR64",            ENCODING_IB)
  ENCODING("VR128",           ENCODING_IB)
  ENCODING("VR256",           ENCODING_IB)
  ENCODING("FR32X",           ENCODING_IB)
  ENCODING("FR64X",           ENCODING_IB)
  ENCODING("VR128X",          ENCODING_IB)
  ENCODING("VR256X",          ENCODING_IB)
  ENCODING("VR512",           ENCODING_IB)
  errs() << "Unhandled immediate encoding " << s << "\n";
  llvm_unreachable("Unhandled immediate encoding");
}
