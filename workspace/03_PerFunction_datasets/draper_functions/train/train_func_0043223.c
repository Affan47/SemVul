InitFromFile(const QString &filename)
  {
    QByteArray key;
    if(ReadFile(filename, key)) {
      return InitFromByteArray(key);
    }

    return false;
  }
