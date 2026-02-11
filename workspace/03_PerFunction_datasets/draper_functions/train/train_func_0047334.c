ParseUrl(const QString &name, const QVariant &value,
          QList<QUrl> &list)
  {
    QUrl url(value.toString());
    if(url.isValid()) {
      list << url;
    } else {
      qCritical() << "Invalid " << name << ": " << value.toString();
    }
  }
