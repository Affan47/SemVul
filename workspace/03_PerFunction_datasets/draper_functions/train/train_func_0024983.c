GeneratePadWithServer(uint server_idx, uint length)
  {
    QByteArray server_pad(length, 0);

    _rngs_with_servers[server_idx]->GenerateBlock(server_pad);
    return server_pad;
  }
