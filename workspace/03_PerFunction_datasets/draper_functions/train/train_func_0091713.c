newOid()
{
    if (*this != MSOid::null)
	return;

    if (!_hid)
    {
#if defined(MS_HAS_SYSTEMINFO)
      char buf[128];
      if (sysinfo(SI_HW_SERIAL, buf, 128) == -1)
       {
         cerr<<"sysinfo: Can't get serial number."<<endl;
         _hid=1;
       }
      else _hid=strtoul(buf,NULL,0);
#else
        _hid = gethostid();
#endif
	newPid();
    }


    struct timeval tval;

    if (MSOid::_seq == SEQUENCE_MAX)
    {
        gettimeofday(&tval, (struct timezone *)NULL);
        if (tval.tv_sec > MSOid::_sec)
            MSOid::_sec = tval.tv_sec;
        else
            MSOid::_sec += 1;
        MSOid::_seq = 0;
    }
    else
        MSOid::_seq += 1;


    _oid[0] = MSOid::_seq << SEQUENCE_SHIFT;
    _oid[0] += VERSIONID << VERSION_SHIFT;
    _oid[1] = _hid;
    _oid[2] = MSOid::_sec;
    _oid[3] = _pid;
}
