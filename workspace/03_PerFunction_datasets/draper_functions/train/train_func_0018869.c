childNode( int ix ) {
  createIndex();
  if (indexed_) {

    return index_[ix];
  } else {

    int n = nChildren();
    ix = n - ix -1;
    Node *nd;
    for ( nd = child_; nd; nd = nd->next_ ) {
      if ( !ix-- ) break;
      if ( !nd ) break;
    }
    return nd;
  }
}
