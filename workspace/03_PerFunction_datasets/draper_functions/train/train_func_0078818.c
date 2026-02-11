appendToText(const char *ptr)
{
  outputString += QString(ptr);
  for (const char *cptr = ptr; *cptr; cptr++) {
    if (*cptr == '\r')
      continue;
    if (*cptr == '\n') {
      textEdit->appendPlainText(QString::fromStdString(bufferedOut));
      bufferedOut = "";
      continue;
    }
    bufferedOut += *cptr;
  }
}
