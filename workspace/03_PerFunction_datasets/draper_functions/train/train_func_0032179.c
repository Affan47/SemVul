onCmdSortArtistList(FXObject*,FXSelector,void*){
  if (artistlist->getSortFunc()==artist_list_sort) {
    artistlist->setSortFunc(artist_list_sort_reverse);
    reverse_artist=true;
    artistlistheader->setArrowState(ARROW_UP);
    }
  else {
    artistlist->setSortFunc(artist_list_sort);
    reverse_artist=false;
    artistlistheader->setArrowState(ARROW_DOWN);
    }

  sortArtists();

  if (tracklist->getSortMethod()==HEADER_BROWSE)
    sortTracks();
  return 1;
  }
