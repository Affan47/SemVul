Tk_CreatePictImageFormat(formatPtr)
    Tk_PictImageFormat *formatPtr;


{
    Tk_PictImageFormat *copyPtr;

#ifdef DEBUG
    printf("Tk_CreatePictImageFormat\n");
#endif

    copyPtr = (Tk_PictImageFormat *) ckalloc(sizeof(Tk_PictImageFormat));
    if(copyPtr == NULL ) {
      (void)fprintf(stderr,"Tk_CreatePictImageFormat: Could not allocate memory\n");
      return;
    }
    *copyPtr = *formatPtr;
    copyPtr->name = (char *) ckalloc((unsigned) (strlen(formatPtr->name) + 1));
    if(copyPtr->name == NULL ) {
      (void)fprintf(stderr,"Tk_CreatePictImageFormat: Could not allocate memory\n");
      return;
    }
    strcpy(copyPtr->name, formatPtr->name);
    copyPtr->nextPtr = formatList;
    formatList = copyPtr;
}
