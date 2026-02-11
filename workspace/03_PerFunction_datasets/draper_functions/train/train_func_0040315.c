ListColorInfo(FILE *file,ExceptionInfo *exception)
{
  register long
    i;

  register const ColorInfo
    *p;

  if (file == (const FILE *) NULL)
    file=stdout;
  (void) GetColorInfo("*",exception);
  LockSemaphoreInfo(color_semaphore);
  for (p=color_list; p != (const ColorInfo *) NULL; p=p->next)
  {
    if ((p->previous == (ColorInfo *) NULL) ||
        (LocaleCompare(p->path,p->previous->path) != 0))
      {
        if (p->previous != (ColorInfo *) NULL)
          (void) fprintf(file,"\n");
        if (p->path != (char *) NULL)
          (void) fprintf(file,"Path: %.1024s\n\n",p->path);
        (void) fprintf(file,
          "Name                   Color                   Compliance\n");
        (void) fprintf(file,"-------------------------------------------------"
          "------------------------------\n");
      }
    if (p->stealth)
      continue;

    (void) fprintf(file,"%.1024s",p->name);
    for (i=(long) strlen(p->name); i <= 22; i++)
      (void) fprintf(file," ");

    if (p->color.opacity == OpaqueOpacity)
      (void) fprintf(file,"%5d,%5d,%5d       ",
		     ScaleQuantumToChar(p->color.red),
		     ScaleQuantumToChar(p->color.green),
		     ScaleQuantumToChar(p->color.blue));
    else
      (void) fprintf(file,"%5d,%5d,%5d,%5d ",
		     ScaleQuantumToChar(p->color.red),
		     ScaleQuantumToChar(p->color.green),
		     ScaleQuantumToChar(p->color.blue),
		     ScaleQuantumToChar(p->color.opacity));
    if ((unsigned int) p->compliance & (unsigned int) SVGCompliance)
      (void) fprintf(file,"SVG ");
    if ((unsigned int) p->compliance & (unsigned int) X11Compliance)
      (void) fprintf(file,"X11 ");
    if ((unsigned int) p->compliance & (unsigned int) XPMCompliance)
      (void) fprintf(file,"XPM ");
    (void) fprintf(file,"\n");
  }
  (void) fflush(file);
  UnlockSemaphoreInfo(color_semaphore);
  return(True);
}
