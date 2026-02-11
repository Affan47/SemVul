memoryEncodingFromString
  (const std::string &s,
   bool hasOpSizePrefix) {
  ENCODING("i16mem",          ENCODING_RM)
  ENCODING("i32mem",          ENCODING_RM)
  ENCODING("i64mem",          ENCODING_RM)
  ENCODING("i8mem",           ENCODING_RM)
  ENCODING("ssmem",           ENCODING_RM)
  ENCODING("sdmem",           ENCODING_RM)
  ENCODING("f128mem",         ENCODING_RM)
  ENCODING("f256mem",         ENCODING_RM)
  ENCODING("f64mem",          ENCODING_RM)
  ENCODING("f32mem",          ENCODING_RM)
  ENCODING("i128mem",         ENCODING_RM)
  ENCODING("i256mem",         ENCODING_RM)
  ENCODING("f80mem",          ENCODING_RM)
  ENCODING("lea32mem",        ENCODING_RM)
  ENCODING("lea64_32mem",     ENCODING_RM)
  ENCODING("lea64mem",        ENCODING_RM)
  ENCODING("opaque32mem",     ENCODING_RM)
  ENCODING("opaque48mem",     ENCODING_RM)
  ENCODING("opaque80mem",     ENCODING_RM)
  ENCODING("opaque512mem",    ENCODING_RM)
  errs() << "Unhandled memory encoding " << s << "\n";
  llvm_unreachable("Unhandled memory encoding");
}
