setCurrentDrawingData(ArDrawingData *data,
						   bool takeOwnershipOfData)
{
  if (myCurrentDrawingData != NULL && myOwnCurrentDrawingData)
  {
    delete myCurrentDrawingData;
    myCurrentDrawingData = NULL;
    myOwnCurrentDrawingData = false;
  }
  myCurrentDrawingData = data;
  myOwnCurrentDrawingData = takeOwnershipOfData;
}
