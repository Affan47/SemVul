SameDev(ConStream *master) const
{
  struct stat sbone, sbtwo;

  if( master == this || Fileno() == master->Fileno() ) return 1;
  else if( Fileno() < 0 || master->Fileno() < 0 ) return 0;

  if( !fstat(Fileno(), &sbone) && !fstat(master->Fileno(), &sbtwo) )
    return (sbone.st_dev==sbtwo.st_dev && sbone.st_ino==sbtwo.st_ino) ? 1 : 0;
  else return 0;
}
