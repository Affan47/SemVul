KDatagramSocket(QObject* parent)
  : KClientSocketBase(parent), d(0L)
{
  peerResolver().setFamily(KResolver::KnownFamily);
  localResolver().setFamily(KResolver::KnownFamily);

  peerResolver().setSocketType(SOCK_DGRAM);
  localResolver().setSocketType(SOCK_DGRAM);

  localResolver().setFlags(KResolver::Passive);


  QObject::connect(&peerResolver(),
		   SIGNAL(finished(KNetwork::KResolverResults)),
  		   this, SLOT(lookupFinishedPeer()));
  QObject::connect(this, SIGNAL(hostFound()), this, SLOT(lookupFinishedLocal()));
}
