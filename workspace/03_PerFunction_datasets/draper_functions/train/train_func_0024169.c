evaluate8Bit(DCM_OBJECT* obj)
{
  CONDITION cond;
  static unsigned char pixels[33];
  void* ctx = 0;
  U32 length = 0;

  DCM_ELEMENT e =
	{ DCM_PXLPIXELDATA, DCM_OB, "", 0, sizeof(pixels), (void*)pixels };

  cond = DCM_GetElementValue(&obj, &e, &length, &ctx);
  if (cond != DCM_NORMAL) {
    COND_DumpConditions();
    exit(3);
  }
  if (length != 32) {
    fprintf(stderr, "Expected 32 bytes, retrieved %d bytes\n", length);
    exit(3);
  }

  if (strcmp(pixels, ("ABCDEFGH" "IJKLMNOP" "QRSTUVWX" "YZ012345")) != 0) {
    fprintf(stderr, "Error in retrieving 8 bit pixels\n");
    fprintf(stderr, "Expected: %s\n",
	    ("ABCDEFGH" "IJKLMNOP" "QRSTUVWX" "YZ012345"));
    pixels[32] = '\0';
    fprintf(stderr, "Received: %s\n", pixels);
  }
}
