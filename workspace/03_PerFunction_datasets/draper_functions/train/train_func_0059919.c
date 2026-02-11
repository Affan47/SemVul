handle_message(bool& reading,
	       QString& mes,
	       const QString& arg)
{
  if (!reading)
  {
    reading = true;
    mes = "";
  }

  if (arg == "+OK")
  {
    reading = false;
    return true;
  }

  mes.append(arg + "\n");
  return false;
}
