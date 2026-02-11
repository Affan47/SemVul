updateSource(GMSource * src){
  FXTreeItem * item = sourcelist->getFirstItem();
  while(item) {
    if (item->getData()==src) {
      item->setText(tr(src->getName().text()));
      break;
      }
    item=item->getNext();
    }
  resort();
  }
