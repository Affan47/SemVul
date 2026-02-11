generate_kpk_bitbase(uint8_t bitbase[]) {

  Bitbase = new Result[IndexMax];
  initialize();


  while(next_iteration());


  int i, j, b;
  for(i = 0; i < 24576; i++) {
    for(b = 0, j = 0; j < 8; b |= (compress_result(Bitbase[8*i+j]) << j), j++);
    bitbase[i] = b;
  }


  delete [] Bitbase;
}
