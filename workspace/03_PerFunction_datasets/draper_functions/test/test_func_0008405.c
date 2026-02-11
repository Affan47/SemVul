setUseWrongEndChars(bool useWrongEndChars)
{
  myUseWrongEndChars = useWrongEndChars;
  std::list<ArSocket *>::iterator it;
  for (it = myConnectingConns.begin(); it != myConnectingConns.end(); ++it)
    (*it)->setStringUseWrongEndChars(useWrongEndChars);
  for (it = myConns.begin(); it != myConns.end(); ++it)
    (*it)->setStringUseWrongEndChars(useWrongEndChars);
}
