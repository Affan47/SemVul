TunnelData(const Request &request)
  {
    const QVariant payload = request.GetData();
    if(!payload.canConvert(QVariant::Hash)) {
      qWarning() << QString("Cannot unserialize tunnel data of type %1").arg(payload.typeName());
      return;
    }

    const QVariantHash hash = payload.toHash();
    if(!hash["data"].canConvert(QVariant::ByteArray)) {
      qWarning() << QString("Cannot unserialize hash[data] of type %1").arg(hash["data"].typeName());
      return;
    }

    const QByteArray data = hash["data"].toByteArray();
    if(data.isEmpty()) return;

    DownstreamData(data);
  }
