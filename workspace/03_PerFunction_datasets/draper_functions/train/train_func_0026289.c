getTargetNodeName(unsigned Opcode) const
{
  if (node_names.empty()) {
    node_names[(unsigned) SPUISD::RET_FLAG] = "SPUISD::RET_FLAG";
    node_names[(unsigned) SPUISD::Hi] = "SPUISD::Hi";
    node_names[(unsigned) SPUISD::Lo] = "SPUISD::Lo";
    node_names[(unsigned) SPUISD::PCRelAddr] = "SPUISD::PCRelAddr";
    node_names[(unsigned) SPUISD::AFormAddr] = "SPUISD::AFormAddr";
    node_names[(unsigned) SPUISD::IndirectAddr] = "SPUISD::IndirectAddr";
    node_names[(unsigned) SPUISD::LDRESULT] = "SPUISD::LDRESULT";
    node_names[(unsigned) SPUISD::CALL] = "SPUISD::CALL";
    node_names[(unsigned) SPUISD::SHUFB] = "SPUISD::SHUFB";
    node_names[(unsigned) SPUISD::SHUFFLE_MASK] = "SPUISD::SHUFFLE_MASK";
    node_names[(unsigned) SPUISD::CNTB] = "SPUISD::CNTB";
    node_names[(unsigned) SPUISD::PREFSLOT2VEC] = "SPUISD::PREFSLOT2VEC";
    node_names[(unsigned) SPUISD::VEC2PREFSLOT] = "SPUISD::VEC2PREFSLOT";
    node_names[(unsigned) SPUISD::SHL_BITS] = "SPUISD::SHL_BITS";
    node_names[(unsigned) SPUISD::SHL_BYTES] = "SPUISD::SHL_BYTES";
    node_names[(unsigned) SPUISD::VEC_ROTL] = "SPUISD::VEC_ROTL";
    node_names[(unsigned) SPUISD::VEC_ROTR] = "SPUISD::VEC_ROTR";
    node_names[(unsigned) SPUISD::ROTBYTES_LEFT] = "SPUISD::ROTBYTES_LEFT";
    node_names[(unsigned) SPUISD::ROTBYTES_LEFT_BITS] =
            "SPUISD::ROTBYTES_LEFT_BITS";
    node_names[(unsigned) SPUISD::SELECT_MASK] = "SPUISD::SELECT_MASK";
    node_names[(unsigned) SPUISD::SELB] = "SPUISD::SELB";
    node_names[(unsigned) SPUISD::ADD64_MARKER] = "SPUISD::ADD64_MARKER";
    node_names[(unsigned) SPUISD::SUB64_MARKER] = "SPUISD::SUB64_MARKER";
    node_names[(unsigned) SPUISD::MUL64_MARKER] = "SPUISD::MUL64_MARKER";
  }

  std::map<unsigned, const char *>::iterator i = node_names.find(Opcode);

  return ((i != node_names.end()) ? i->second : 0);
}
