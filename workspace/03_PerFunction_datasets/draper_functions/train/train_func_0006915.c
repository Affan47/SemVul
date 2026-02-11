bmphide(tBMPHIDE* record, unsigned char* t, FILE* inputFile, FILE* outputFile){
  tBMPHIDEText* text = (tBMPHIDEText*) malloc(sizeof(tBMPHIDEText));
  if (text == NULL)
    BMPHideError("Not enough memory.");
  text->size = strlen(t);
  text->index = 0;
  text->bitIndex = 7;
  text->data = t;

  BMPHideReadBMP(inputFile);

  int pictureBytes = BMPInfo.biWidth * BMPInfo.biHeight * 3;
  int textBytes = text->size;
  int textBits = textBytes * 8;
  NLSBS = (textBits / pictureBytes) + 1;

  if (VERBOSE)
    printf("LSBS used: %d\n", NLSBS);
  if (NLSBS > 7){
    return BMPHideError("Text is too long.");
  }


  BMPHideHideText(text);
  BMPhideSaveBMP(outputFile);

  if (VERBOSE){
    printf("TEXT: %s\n", text->data);
    printf("TEXT IN BINARY FORMAT: \n");
    text->index = 0;
    text->bitIndex = 7;
    int i;
    for (i = 0; i < text->size * 8; i++)
      printf("%d", BMPHideGetTextBit(text));
    printf("\n");
  }

  free(text);
  return BMPHIDEOk;
}
