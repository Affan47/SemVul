readnextaction ( void )
{
      if ( stream->dataavail () )
         nextaction = stream->readChar();
      else
         nextaction = rpl_finished;
}
