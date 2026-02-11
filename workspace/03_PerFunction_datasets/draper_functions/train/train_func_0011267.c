tapeConfigLoadCbk (void *data)
{
  int rval = 1 ;
  long iv ;
  int bv ;
  FILE *fp = (FILE *) data ;
  char *dir, *p ;

  if (getString (topScope,"backlog-directory",&p,NO_INHERIT))
    {
      dir = concatpath(innconf->pathspool, p);
      free(p);
      if (tapeDirectory != NULL && strcmp (tapeDirectory,dir) != 0)
        {
          warn ("ME config: cannot change backlog-directory of a running"
                " process") ;
          free (dir) ;
          dir = xstrdup (tapeDirectory) ;
        }

      if (!isDirectory (dir) && isDirectory (dflTapeDir))
        {
          logOrPrint (LOG_ERR,fp,
                      "ME config: definition of backlog-directory (%s) is a"
                      " non-existant directory. Using %s",
                      dir,dflTapeDir) ;
          free (dir) ;
          dir = xstrdup (dflTapeDir) ;
        }
      else if (!isDirectory (dir))
        logAndExit (1,"ME config: no usable value for backlog-directory") ;
    }
  else if (!isDirectory (dflTapeDir))
  {
    logAndExit (1,"ME config: no usable value for backlog-directory") ;
    return -1;
  }
  else
    dir = xstrdup (dflTapeDir) ;

  if (tapeDirectory != NULL)
    free (tapeDirectory) ;
  tapeDirectory = dir ;


  if (getInteger (topScope,"backlog-highwater",&iv,NO_INHERIT))
    {
      if (iv < 0)
        {
          rval = 0 ;
          logOrPrint (LOG_ERR,fp,
                      "ME config: value of %s (%ld) in %s cannot be less"
                      " than 0. Using %ld","backlog-highwater",
                      iv,"global scope",(long)TAPE_HIGHWATER);
          iv = TAPE_HIGHWATER ;
        }
    }
  else
    iv = TAPE_HIGHWATER ;
  tapeHighwater = (unsigned int) iv ;


  if (getInteger (topScope,"backlog-rotate-period",&iv,NO_INHERIT))
    {
      if (iv < 0)
        {
          rval = 0 ;
          logOrPrint (LOG_ERR,fp,
                      "ME config: value of %s (%ld) in %s cannot be less"
                      " than 0. Using %ld",
                      "backlog-rotate-period",
                      iv,"global scope",(long)TAPE_ROTATE_PERIOD);
          iv = TAPE_ROTATE_PERIOD ;
        }
    }
  else
    iv = TAPE_ROTATE_PERIOD ;
  rotatePeriod = (unsigned int) iv ;


  if (getInteger (topScope,"backlog-ckpt-period",&iv,NO_INHERIT))
    {
      if (iv < 0)
        {
          rval = 0 ;
          logOrPrint (LOG_ERR,fp,
                      "ME config: value of %s (%ld) in %s cannot be less"
                      " than 0. Using %ld",
                      "backlog-ckpt-period",iv,
                      "global scope",(long)TAPE_CHECKPOINT_PERIOD);
          iv = TAPE_CHECKPOINT_PERIOD ;
        }
    }
  else
    iv = TAPE_CHECKPOINT_PERIOD ;
  tapeCkPtPeriod = (unsigned int) iv ;


  if (getInteger (topScope,"backlog-newfile-period",&iv,NO_INHERIT))
    {
      if (iv < 0)
        {
          rval = 0 ;
          logOrPrint (LOG_ERR,fp,
                      "ME config: value of %s (%ld) in %s cannot be less"
                      " than 0. Using %ld",
                      "backlog-newfile-period",
                      iv,"global scope",(long)TAPE_NEWFILE_PERIOD);
          iv = TAPE_NEWFILE_PERIOD ;
        }
    }
  else
    iv = TAPE_NEWFILE_PERIOD ;
  tapeCkNewFilePeriod = (unsigned int) iv ;


  if (getBool (topScope,"debug-shrinking",&bv,NO_INHERIT))
    debugShrinking = (bv ? true : false) ;

  return rval ;
}
