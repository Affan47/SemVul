ParseLine(const char *buffer)
{
  vector<string> vs;

  if (buffer[0] == '#')
    return;

  if (EQn(buffer,"TRANSFORM",7))
  {

    tokenize(vs, buffer, " >\t\n");
    OBChemTsfm tr;
    if (vs.empty() || vs.size() < 3 || vs[1].empty() || vs[2].empty())
    {
      string mes("Could not parse line:\n");
      obErrorLog.ThrowError(__FUNCTION__, mes + buffer, obWarning);
    }
    else
    {
      if(!tr.Init(vs[1],vs[2]))
      {
        string mes("Could not make valid transform from the line:\n");
        obErrorLog.ThrowError(__FUNCTION__, mes + buffer, obWarning);
      }
      else
        _transforms.push_back(tr);
    }
  }
}
