zoneOffset(const char *zoneName_) const
{


  struct zoneoff *zp = (struct zoneoff *)zoneHashTable()->lookup(zoneName_);
  if (zp==(struct zoneoff *)zoneHashTable()->notFound())
    {
      MSMessageLog::warningMessage("Invalid timezone:  \"%s\"\n",zoneName_);
      return 0;
    }
  else
    {
      return zoneOffset(zp->zone);
    }
}
