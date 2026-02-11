param(float val) {
  if (_nParams < _maxParams) {
    _params[_nParams].type = GIMP_PDB_FLOAT;
    _params[_nParams].data.d_float = val;
    _nParams++;
  }
  return *this;
}
