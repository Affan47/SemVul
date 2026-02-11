getTrackFilenames(const FXIntList & tracks,FXStringList & files){
  files.no(tracks.no());
  for (int i=0;i<tracks.no();i++){
    files[i]=db->getTrackFilename(tracks[i]);
    }
  }
