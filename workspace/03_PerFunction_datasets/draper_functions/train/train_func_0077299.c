Derandomize(const QByteArray &randomized_msg) const
  {
    QByteArray seed = randomized_msg.mid(0, GetHeaderLength());
    QByteArray tail = randomized_msg.mid(GetHeaderLength());

    return PadWithSeed(seed, tail);
  }
