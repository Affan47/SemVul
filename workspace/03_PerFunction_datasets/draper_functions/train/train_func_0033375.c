WriteToStream(QTextStream& ostream)
  {
    QString resp_body = GetBody();
    AddHeader("Content-Length", QString("%1").arg(resp_body.length()));

    qDebug() << "Starting to write";
    ostream << _http_version << " ";
    ostream << _status_code << " " << _status_map[_status_code];
    ostream << _eol;

    QHash<QString, QString>::iterator i;
    for(i=_header_map.begin(); i!=_header_map.end(); ++i) {
      ostream << i.key() << ": " << i.value() << _eol;
    }
    ostream << _eol;
    ostream << resp_body;
  }
