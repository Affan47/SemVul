BuildMsgsList( void ) {
  l_msgs.Clear();

  if ( cur_lang ) {
    const char *m;

    for ( int i = 0; (m = cur_lang->GetMsg(i)) != 0; ++i ) {
      l_msgs.AddTail( new TLWNode(string(m).substr(0, 30).c_str(), const_cast<char *>(m), i) );
    }
  }
}
