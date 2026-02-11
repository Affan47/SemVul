s5bServer ()
{

  if ( !d->s5bServer )
  {
    d->s5bServer = new XMPP::S5BServer ();
    QObject::connect ( d->s5bServer, SIGNAL (destroyed()), this, SLOT (slotS5BServerGone()) );


    if ( fileTransfersEnabled () )
    {
      s5bServer()->start ( d->s5bServerPort );
    }
  }

  return d->s5bServer;

}
