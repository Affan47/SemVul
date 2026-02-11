moveTrack(GMTrackList * tracklist,FXint from,FXint to){
  if (tracklist->getSortMethod()!=HEADER_QUEUE) return false;
  FXint fromq = ((GMDBTrackItem*)tracklist->getItem(from))->getTrackQueue();
  FXint toq = ((GMDBTrackItem*)tracklist->getItem(to))->getTrackQueue();
  db->moveTrack(playlist,fromq,toq);
  if (current_queue==fromq) {
    current_queue=toq;
    }
  else if (fromq<=current_queue && current_queue<=toq) {
    current_queue-=1;
    }
  else if (fromq>=current_queue && current_queue>=toq)  {
    current_queue+=1;
    }
  return true;
  }
