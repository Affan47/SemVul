emitAll(MCStreamer &Streamer) {

  for (ConstantPoolMapTy::iterator CPI = ConstantPools.begin(),
                                   CPE = ConstantPools.end();
       CPI != CPE; ++CPI) {
    MCSection *Section = CPI->first;
    ConstantPool &CP = CPI->second;

    emitConstantPool(Streamer, Section, CP);
  }
}
