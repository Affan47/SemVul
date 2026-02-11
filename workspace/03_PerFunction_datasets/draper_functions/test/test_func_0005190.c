Encrypt(const QVector<QSharedPointer<AsymmetricKey> > &keys,
      const QByteArray &cleartext, QByteArray &ciphertext,
      QVector<QByteArray> *intermediate) const
  {
    if(keys.count() == 0) {
      ciphertext = cleartext;
      return -1;
    }

    ciphertext = keys.first()->Encrypt(cleartext);

    if(ciphertext.isEmpty()) {
      return 0;
    }

    if(intermediate) {
      intermediate->append(ciphertext);
    }

    if(keys.count() == 1) {
      return -1;
    }

    for(int idx = 1; idx < keys.count() - 1; idx++) {
      ciphertext = keys[idx]->Encrypt(ciphertext);

      if(ciphertext.isEmpty()) {
        return idx;
      }

      if(intermediate) {
        intermediate->append(ciphertext);
      }
    }

    ciphertext = keys.last()->Encrypt(ciphertext);

    if(ciphertext.isEmpty()) {
      return keys.count() - 1;
    }

    return -1;
  }
