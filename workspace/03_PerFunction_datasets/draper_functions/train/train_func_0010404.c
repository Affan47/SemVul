fillReadBuf() {
  JPXTileComp *tileComp;
  Guint tileIdx, tx, ty;
  int pix, pixBits;

  do {
    if (curY >= img.ySize) {
      return;
    }
    tileIdx = ((curY - img.yTileOffset) / img.yTileSize) * img.nXTiles
              + (curX - img.xTileOffset) / img.xTileSize;
#if 1
    tileComp = &img.tiles[tileIdx].tileComps[curComp];
#else
    tileComp = &img.tiles[tileIdx].tileComps[havePalette ? 0 : curComp];
#endif
    tx = jpxCeilDiv((curX - img.xTileOffset) % img.xTileSize, tileComp->hSep);
    ty = jpxCeilDiv((curY - img.yTileOffset) % img.yTileSize, tileComp->vSep);
    pix = (int)tileComp->data[ty * (tileComp->x1 - tileComp->x0) + tx];
    pixBits = tileComp->prec;
#if 1
    if (++curComp == img.nComps) {
#else
    if (havePalette) {
      if (pix >= 0 && pix < palette.nEntries) {
	pix = palette.c[pix * palette.nComps + curComp];
      } else {
	pix =
      pixBits = palette.bpc[curComp];
    }
    if (++curComp == (Guint)(havePalette ? palette.nComps : img.nComps)) {
#endif
      curComp = 0;
      if (++curX == img.xSize) {
	curX = img.xOffset;
	++curY;
      }
    }
    if (pixBits == 8) {
      readBuf = (readBuf << 8) | (pix & 0xff);
    } else {
      readBuf = (readBuf << pixBits) | (pix & ((1 << pixBits) - 1));
    }
    readBufLen += pixBits;
  } while (readBufLen < 8);
}
