getPixmapKey (const char picType, const int index)
{
    QString pixmapKey = "";

    int frameCount = (index < 0) ? -1 : keyTable[index].frameCount;
    if (frameCount > -1) {
	pixmapKey = keyTable[index].picKey;
	if (frameCount > 0) {


	    pixmapKey = pixmapKey + QString(keyTable[index].frameSuffix);
	    pixmapKey = pixmapKey.arg (keyTable[index].frameBaseIndex +
				       (rand() % frameCount));
	}
    }
    return pixmapKey;
}
