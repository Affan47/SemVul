allocateWaveMap(const QSize &size)
{
    int **waveMap = new int *[size.width()];
    if (!waveMap) {
        kDebug() << "could not allocate wave map";
        return 0;
    }

    for (int x = 0; x < size.width(); ++x) {
        waveMap[x] = new int[size.height()];
        if (!waveMap[x]) {
            kDebug() << "could not allocate wave map";
            return 0;
        }
    }

    return waveMap;
}
