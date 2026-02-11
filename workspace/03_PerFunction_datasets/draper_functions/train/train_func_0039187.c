HandleConnectionAttemptFailure(
      const Address &addr, const QString &)
  {
    if(!_addr_to_id.contains(addr)) {
      return;
    }

    Id id = _addr_to_id[addr];
    _addr_to_id.remove(addr);
    _local_initiated.remove(id);
  }
