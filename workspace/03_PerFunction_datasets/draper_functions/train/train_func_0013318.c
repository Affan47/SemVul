slotCSDisconnected ()
{


  emit debugMessage ( "Disconnected, freeing up file transfer port..." );


  removeS5BServerAddress ( localAddress () );

  emit csDisconnected ();

}
