close_all() {
  for (ListItr(PipeList) i(_pl); i.more(); i.next()) {
    pclose( i.cur() );
  }

  for (ListItr(FileList) j(_fl); j.more(); j.next()) {
    fclose( j.cur() );
  }

  for (ListItr(StreamList) k(_sl); k.more(); k.next()) {
    delete k.cur();
  }

  forget();
}
