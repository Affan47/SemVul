Trim() {
  if (inst_len_ < inst_cap_) {
    Prog::Inst* ip = new Prog::Inst[inst_len_];
    memmove(ip, inst_, inst_len_ * sizeof ip[0]);
    delete[] inst_;
    inst_ = ip;
    inst_cap_ = inst_len_;
  }
}
