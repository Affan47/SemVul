Optimize() {
  Workq q(size_);


  q.clear();
  AddToQueue(&q, start_);
  for (Workq::iterator i = q.begin(); i != q.end(); ++i) {
    int id = *i;

    Inst* ip = inst(id);
    int j = ip->out();
    Inst* jp;
    while (j != 0 && (jp=inst(j))->opcode() == kInstNop) {
      j = jp->out();
    }
    ip->set_out(j);
    AddToQueue(&q, ip->out());

    if (ip->opcode() == kInstAlt) {
      j = ip->out1();
      while (j != 0 && (jp=inst(j))->opcode() == kInstNop) {
        j = jp->out();
      }
      ip->out1_ = j;
      AddToQueue(&q, ip->out1());
    }
  }


  q.clear();
  AddToQueue(&q, start_);
  for (Workq::iterator i = q.begin(); i != q.end(); ++i) {
    int id = *i;
    Inst* ip = inst(id);
    AddToQueue(&q, ip->out());
    if (ip->opcode() == kInstAlt)
      AddToQueue(&q, ip->out1());

    if (ip->opcode() == kInstAlt) {
      Inst* j = inst(ip->out());
      Inst* k = inst(ip->out1());
      if (j->opcode() == kInstByteRange && j->out() == id &&
          j->lo() == 0x00 && j->hi() == 0xFF &&
          IsMatch(this, k)) {
        ip->set_opcode(kInstAltMatch);
        continue;
      }
      if (IsMatch(this, j) &&
          k->opcode() == kInstByteRange && k->out() == id &&
          k->lo() == 0x00 && k->hi() == 0xFF) {
        ip->set_opcode(kInstAltMatch);
      }
    }
  }
}
