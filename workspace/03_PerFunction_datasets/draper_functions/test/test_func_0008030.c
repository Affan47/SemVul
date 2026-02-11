BroadcastBlameVerification()
  {
    QByteArray msg;
    QDataStream stream(&msg, QIODevice::WriteOnly);
    stream << BLAME_VERIFICATION << GetRoundId() << _state->blame_hash
      << _state->blame_signatures;

    _state->blame_verification_msgs = QVector<HashSig>(GetGroup().Count());

    VerifiableBroadcast(msg);
  }
