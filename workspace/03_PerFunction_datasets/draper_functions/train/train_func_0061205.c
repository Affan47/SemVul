onCmdLoadAlbumIcons(FXObject*,FXSelector,void*ptr){
  FXint item=(FXint)(FXival)ptr;
  if (item>=albumlist->getNumItems()) return 1;
  while(item<albumlist->getNumItems()){
    if (albumlist->getItemIcon(item)!=GMIconTheme::instance()->icon_nocover) {
      item++;
      continue;
      }
    FXint album=(FXint)(FXival)albumlist->getItemData(item);
    if (album==-1){
      item++;
      continue;
      }
    FXIcon * icon = source->getAlbumIcon(album,false);
    if (icon) albumlist->setItemIcon(item,icon);
    break;
    }
  item++;
  if (item>=albumlist->getNumItems()) return 1;
  getApp()->addChore(this,ID_LOAD_ALBUM_ICONS,(void*)(FXival)item);
  return 1;
  }
