AddUserAlibi(uint user_idx, const QBitArray &bits)
  {
    Q_ASSERT(user_idx < _num_users);
    Q_ASSERT(_num_servers == static_cast<uint>(bits.count()));

    for(uint server_idx=0; server_idx<_num_servers; server_idx++) {
      _data[user_idx][server_idx].user_bit = bits[server_idx];
    }
  }
