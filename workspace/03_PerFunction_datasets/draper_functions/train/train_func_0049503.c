GenerateData(int size)
  {
    Crypto::Library *lib = Crypto::CryptoFactory::GetInstance().GetLibrary();
    QSharedPointer<Utils::Random> rng(lib->GetRandomNumberGenerator());
    int maximum = GetGroup().Count();
    int value = rng->GetInt(0, maximum);
    if(float(value) / float(maximum) > PERCENT_ACTIVE) {
      return QByteArray();
    }
    QByteArray data(size, 0);
    rng->GenerateBlock(data);
    return data;
  }
