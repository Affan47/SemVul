httpStatus(const QString& response, bool textStatus = false)
{
  if (response.isEmpty()) {
    return jsUndefined();
  }

  int endOfLine = response.indexOf("\n");
  QString firstLine = (endOfLine == -1) ? response : response.left(endOfLine);
  int codeStart = firstLine.indexOf(" ");
  int codeEnd = firstLine.indexOf(" ", codeStart + 1);

  if (codeStart == -1 || codeEnd == -1) {
    return jsUndefined();
  }

  if (textStatus) {
    QString statusText = firstLine.mid(codeEnd + 1, endOfLine - (codeEnd + 1)).trimmed();
    return jsString(statusText);
  }

  QString number = firstLine.mid(codeStart + 1, codeEnd - (codeStart + 1));

  bool ok = false;
  int code = number.toInt(&ok);
  if (!ok) {
    return jsUndefined();
  }

  return jsNumber(code);
}
