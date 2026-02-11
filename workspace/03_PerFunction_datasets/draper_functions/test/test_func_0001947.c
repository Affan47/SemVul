interrupt_handler(int NotUsed){
  UNUSED_PARAMETER(NotUsed);
  seenInterrupt = 1;
  if( db ) sqlite3_interrupt(db);
}
