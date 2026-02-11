checkDefault(PropertySet &propSet)
{
  if(_nDefs > 0) {

    int hostDimension;
    OfxStatus stat = propSet.propGetDimension(_name, hostDimension);
    (void)stat;

    OFX::logError(hostDimension != _nDefs, "Host reports default dimension of '%s' is %d, which is different to the default value %d;", _name, hostDimension, _nDefs);

    int N = hostDimension < _nDefs ? hostDimension : _nDefs;

    for(int i = 0; i < N; i++) {
      void       *vP;
      int         vI;
      double      vD;
      std::string vS;

      switch(_ilk) {
      case PropertyDescription::ePointer :
        propSet.propGet(_name, vP, i);
        OFX::logError(vP != (void *) _defs[i], "Default value of %s[%d] = %p, it should be %p;", _name, i, vP, (void *) _defs[i]);
        break;
      case PropertyDescription::eInt :
        propSet.propGet(_name, vI, i);
        OFX::logError(vI != (int) _defs[i], "Default value of %s[%d] = %d, it should be %d;", _name, i, vI, (int) _defs[i]);
        break;
      case PropertyDescription::eString  :
        propSet.propGet(_name, vS, i);
        OFX::logError(vS != _defs[i].vString, "Default value of %s[%d] = '%s', it should be '%s';", _name, i, vS.c_str(), _defs[i].vString.c_str());
        break;
      case PropertyDescription::eDouble  :
        propSet.propGet(_name, vD, i);
        OFX::logError(vD != (double) _defs[i], "Default value of %s[%d] = %g, it should be %g;", _name, i, vD, (double) _defs[i]);
        break;
      }
    }
  }
}
