data(const FXchar* str,FXint len){
  if (elem==Elem_Playlist_Title) {
    title.assign(str,len);
    }
  else if (elem==Elem_Playlist_TrackList_Track_Location) {
    FXString url(str,len);
    files.append(url);
    }
  }
