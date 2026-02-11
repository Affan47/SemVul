floodfillFromPixel(VimosPixelAcc *pixAcc, int rank,
                      VimosPixelList *pixList, VimosPixelData *lastPixData)
{
  int vrank;
  int posx, posy;
  VimosPixelData *pixData;


  posx = pixAcc->pos[rank] % pixAcc->imWidth;
  posy = pixAcc->pos[rank] / pixAcc->imWidth;

  pixAcc->accIntensity +=
                pixAcc->refImage->data[posx+posy*pixAcc->imWidth];
  pixAcc->ValidPixels[rank] = FALSE;
  pixAcc->RemainingPixels --;
  pixAcc->PixelsInCurrentBlock++;


  pixData = newPixelData();
  pixData->x = posx;
  pixData->y = posy;
  pixData->value = pixAcc->refImage->data[posx+posy*pixAcc->imWidth];


  if (lastPixData == NULL)
    {

     pixList->pixelData = pixData;
    }
  else
    {

     lastPixData->next = pixData;
     pixData->prev = lastPixData;
    }

  lastPixData = pixData;


  if ((vrank = getPixelrankIfValid(pixAcc, rank, 1)) != 0)
      floodfillFromPixel(pixAcc, vrank, pixList, lastPixData);

  if ((vrank = getPixelrankIfValid(pixAcc, rank, 2)) != 0)
      floodfillFromPixel(pixAcc, vrank, pixList, lastPixData);

  if ((vrank = getPixelrankIfValid(pixAcc, rank, 3)) != 0)
      floodfillFromPixel(pixAcc, vrank, pixList, lastPixData);

  if ((vrank = getPixelrankIfValid(pixAcc, rank, 4)) != 0)
      floodfillFromPixel(pixAcc, vrank, pixList, lastPixData);

}
