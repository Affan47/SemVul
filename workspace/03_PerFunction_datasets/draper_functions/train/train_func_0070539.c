prettyName() const
{
  QString res = _name;

  if (_name.isEmpty())
      return prettyEmptyName();

  if (GlobalConfig::hideTemplates()) {

      res = QString();
      int d = 0;
      for(int i=0;i<_name.length();i++) {
          switch(_name[i].toLatin1()) {
          case '<':
              if (d<=0) res.append(_name[i]);
              d++;
              break;
          case '>':
              d--;

          default:
              if (d<=0) res.append(_name[i]);
              break;
          }
      }
  }
#if 0


  int p = _name.indexOf('(');
  if (p>0) {

    if ( (p+2 < _name.size()) && (_name[p+1] == ')') && (_name[p+2] == '(')) p+=2;


    if (isUniquePrefix(_name.left(p+1)))
      res = _name.left(p);
  }
#endif


  if (_cycle) {
    if (_cycle != this)
      res = QString("%1 <cycle %2>").arg(res).arg(_cycle->cycleNo());
    else
      res = QString("<cycle %2>").arg(_cycle->cycleNo());
  }


  return res;
}
