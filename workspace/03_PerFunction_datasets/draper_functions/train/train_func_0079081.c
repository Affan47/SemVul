addTapeGlobally (Tape tape)
{
  ASSERT (tape != NULL) ;

  if (activeTapeSize == activeTapeIdx)
    {
      u_int i ;

      activeTapeSize += 10 ;
      if (activeTapes != NULL)
        activeTapes = REALLOC (activeTapes, Tape, activeTapeSize) ;
      else
        activeTapes = ALLOC (Tape, activeTapeSize) ;

      ASSERT (activeTapes != NULL) ;

      for (i = activeTapeIdx ; i < activeTapeSize ; i++)
        activeTapes [i] = NULL ;
    }
  activeTapes [activeTapeIdx++] = tape ;
}
