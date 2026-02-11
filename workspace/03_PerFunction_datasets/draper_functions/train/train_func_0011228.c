writeMultiLineComment(const char *comment,
                                                 FILE *file,
                                                 char *lineBuf,
                                                 int lineBufSize,
                                                 const char *startComment)
{
  if ((comment == NULL) ||
      (file == NULL) ||
      (lineBuf == NULL) ||
      (lineBufSize <= 0) ||
      (startComment == NULL)) {
    ArLog::log(ArLog::Normal,
               "ArConfigArg::writeMultiLineComment() invalid input");
    return false;
  }


  ArArgumentBuilder descr;
  descr.setQuiet(true);
  descr.addPlain(comment);

  for (unsigned int i = 0; i < descr.getArgc(); i++)
  {


    if (strlen(lineBuf) + strlen(descr.getArg(i)) > 78)
    {
      fprintf(file, "%s\n", lineBuf);

      sprintf(lineBuf, startComment, "");
      sprintf(lineBuf, "%s %s", lineBuf, descr.getArg(i));
    }

    else {

      sprintf(lineBuf, "%s %s", lineBuf, descr.getArg(i));
    }
  }

  fprintf(file, "%s\n", lineBuf);

  return true;

}
