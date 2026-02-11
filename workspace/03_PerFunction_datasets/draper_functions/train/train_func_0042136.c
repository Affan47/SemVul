RunBlameShuffle()
  {
    ResetBlameData();

    qDebug() << "Starting blame shuffle";
    _blame_shuffle_round->Start();
  }
