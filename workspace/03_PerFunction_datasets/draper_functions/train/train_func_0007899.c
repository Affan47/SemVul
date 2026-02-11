Shutdown()
{
  if (_VM) {
    Cleanup();
#if 0
    sq_release(_VM,&_root->_o);
    sq_resetobject(&_root->_o);
#endif
    delete _root;
    _root = NULL;
    HSQUIRRELVM v = _VM;
    _VM = NULL;
    sq_close(v);
  }
}
