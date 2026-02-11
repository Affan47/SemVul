luaLoad()
{

  luaLoadWhenAccepting = false;
  if (e->document()->isEmpty())
    return true;

  QByteArray cmd;
  if (fileName.isEmpty() || e->document()->isModified())
    {
      cmd = "qtide.doeditor(qt." + q->objectName().toLocal8Bit() + ")";
    }
  else
    {
      cmd = "dofile('";
      QByteArray f = fileName.toLocal8Bit();
      for (int i=0; i<f.size(); i++)
        if (isascii(f[i]) && isprint(f[i]) && f[i]!='\"' && f[i]!='\'')
          cmd += f[i];
        else {
          char buf[8];
          sprintf(buf,"\\%03o", (unsigned char)f[i]);
          cmd += buf;
        }
      cmd += "\')";
    }
  return luaEval(cmd);
}
