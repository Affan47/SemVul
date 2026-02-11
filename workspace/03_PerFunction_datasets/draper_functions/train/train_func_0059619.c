postCheckpoint ( const dmtcp::vector<int>& fds, bool isRestart )
{
  restoreOptions ( fds );
  if (_checkpointed && isRestart && _type == FILE_DELETED) {


     if (jalib::Filesystem::FileExists(_path)) {
      JWARNING( unlink(_path.c_str()) != -1 ) (_path)
        .Text("The file was unlinked at the time of checkpoint. "
              "Unlinking it after restart failed");
     }
  }
}
