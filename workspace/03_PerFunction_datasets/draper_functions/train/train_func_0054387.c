WidgetActivated( Widget *widget, Window *win ) {
  Node *node = static_cast<ListWidget *>(widget)->Selected();
  GUI_Status rc = GUI_OK;

  if ( node ) {
    if ( node == last ) rc = ok->Activate();
    else {
      str->SetString( static_cast<TLWNode *>(node)->Name() );
      last = node;
    }
  }
  return rc;
}
