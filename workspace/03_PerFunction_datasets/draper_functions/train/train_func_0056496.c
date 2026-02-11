ProcessNextChunk (CModel *model, Chunk *previousChunk)
{
  char version [10];
  char buf [STDSIZE];
  CObject newObject;
  CMaterial newTexture;

  currentChunk = new Chunk;
  if (currentChunk == NULL) error_outofmemory ();

  while (previousChunk->bytesRead < previousChunk->length)
  {
    ReadChunk(currentChunk);
  	if (currentChunk->ID == 0 && currentChunk->length == 0) exit (1000);
    if (debug3ds) { fprintf (debugstream3ds, "%X: ", currentChunk->ID); fflush (debugstream3ds); }

    switch (currentChunk->ID)
    {
      case VERSION:
        currentChunk->bytesRead += file->readString (version, 10, currentChunk->length - currentChunk->bytesRead);
        if (version [0] > 0x03)
        {
          sprintf (buf, "This 3DS file is over version 3 so it may load incorrectly");
          display (buf, LOG_WARN);
        }
        if (debug3ds) { fprintf (debugstream3ds, "Version %d\n", version [0]); fflush (debugstream3ds); }
        break;

      case OBJECTINFO:
        ReadChunk (tempChunk);
        tempChunk->bytesRead += file->readString (version, 10, tempChunk->length - tempChunk->bytesRead);
        currentChunk->bytesRead += tempChunk->bytesRead;
        ProcessNextChunk (model, currentChunk);
        break;

      case MATERIAL:
        model->addMaterial (&newTexture);
        ProcessNextMaterialChunk (model, currentChunk);
        break;

      case OBJECT:
        model->addObject (&newObject);
        memset (&newObject, 0, sizeof (CObject));
        currentChunk->bytesRead += GetString (model->object [model->numObjects - 1]->name);
        ProcessNextObjectChunk (model, (model->object [model->numObjects - 1]), currentChunk);
        break;

      case MAINSCALE:
        float mainscale;
        currentChunk->bytesRead += file->readFloat (&mainscale);
        model->scale = mainscale;
        currentChunk->bytesRead += file->skip (currentChunk->length - currentChunk->bytesRead);
        break;

      case EDITKEYFRAME:
        currentChunk->bytesRead += file->skip (currentChunk->length - currentChunk->bytesRead);
        break;

      default:
        currentChunk->bytesRead += file->skip (currentChunk->length - currentChunk->bytesRead);
        break;
    }

    previousChunk->bytesRead += currentChunk->bytesRead;
  }
  delete currentChunk;
  currentChunk = previousChunk;
}
