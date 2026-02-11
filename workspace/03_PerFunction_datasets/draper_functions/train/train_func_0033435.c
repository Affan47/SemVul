CreateDescriptor(const QByteArray &data)
  {
    int length = data.size();

    Library *lib = CryptoFactory::GetInstance().GetLibrary();
    QScopedPointer<Hash> hashalgo(lib->GetHashAlgorithm());

    QByteArray xor_message(length, 0);
    QVector<QByteArray> hashes;

    int my_idx = GetGroup().GetIndex(GetLocalId());

    foreach(const PublicIdentity &gc, GetGroup().GetRoster()) {
      QByteArray seed = _anon_dh->GetSharedSecret(gc.GetDhKey());

      if(hashes.size() == my_idx) {
        hashes.append(QByteArray());
        continue;
      }

      QByteArray msg(length, 0);
      QScopedPointer<Random> rng(lib->GetRandomNumberGenerator(seed));
      rng->GenerateBlock(msg);
      hashes.append(hashalgo->ComputeHash(msg));
      Xor(xor_message, xor_message, msg);
    }

    QByteArray my_xor_message = QByteArray(length, 0);
    Xor(my_xor_message, xor_message, data);
    SetMyXorMessage(my_xor_message);
    hashes[my_idx] = hashalgo->ComputeHash(my_xor_message);

    QByteArray hash = hashalgo->ComputeHash(data);

    Descriptor descriptor(length, _anon_dh->GetPublicComponent(), hashes, hash);
    SetMyDescriptor(descriptor);
  }
