SendServerAlibis(const QMap<int, Accusation> &map)
  {
    QByteArray alibi_bytes;
    for(QMap<int, Accusation>::const_iterator i=map.constBegin(); i!=map.constEnd(); ++i) {
      Accusation acc = i.value();
      QByteArray al = _server_alibi_data.GetAlibiBytes(i.key(), acc);
      alibi_bytes.append(al);
    }

    QByteArray packet;
    QDataStream stream(&packet, QIODevice::WriteOnly);
    stream << MessageType_ServerAlibiData << GetRoundId() << _phase << alibi_bytes;
    VerifiableBroadcast(packet);
  }
