quit_eval() {
  for(int i = 0; i < THREAD_MAX; i++) {
    delete PawnTable[i];
    delete MaterialTable[i];
  }
}
