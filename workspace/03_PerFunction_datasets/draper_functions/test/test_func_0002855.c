mergeWith ( const Connection& _that ){
  const FileConnection& that = (const FileConnection&)_that;
  JTRACE("Merging file connections") (_path) (_type) (that._path) (that._type);
  Connection::mergeWith(_that);
  JWARNING(_path   == that._path)   MERGE_MISMATCH_TEXT;
  JWARNING(_offset == that._offset) MERGE_MISMATCH_TEXT;
  if (!_checkpointed) {
    _checkpointed = that._checkpointed;
    _rel_path     = that._rel_path;
    _ckptFilesDir = that._ckptFilesDir;
    _restoreInSecondIteration = that._restoreInSecondIteration;
  }


}
