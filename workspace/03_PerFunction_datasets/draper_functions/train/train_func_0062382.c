browseSort(const GMTrackItem * pa,const GMTrackItem * pb){
  const GMDBTrackItem * const ta = (GMDBTrackItem*)pa;
  const GMDBTrackItem * const tb = (GMDBTrackItem*)pb;
  register FXint a=0,b=0,x;
  if (GMTrackView::album_by_year) {
    if (ta->album_year > tb->album_year)
      return (GMTrackView::reverse_album) ? -1 : 1;
    else if (ta->album_year < tb->album_year)
      return (GMTrackView::reverse_album) ? 1 : -1;
    }

  if (begins_with_keyword(ta->album)) a=FXMIN(ta->album.length()-1,ta->album.find(' ')+1);
  if (begins_with_keyword(tb->album)) b=FXMIN(tb->album.length()-1,tb->album.find(' ')+1);
  x = comparecase(&ta->album[a],&tb->album[b]);

  if (x!=0)
    return (GMTrackView::reverse_album) ? -x : x;

  a=b=0;
  if (begins_with_keyword(ta->album_artist)) a=FXMIN(ta->album_artist.length()-1,ta->album_artist.find(' ')+1);
  if (begins_with_keyword(tb->album_artist)) b=FXMIN(tb->album_artist.length()-1,tb->album_artist.find(' ')+1);
  x = comparecase(&ta->album_artist[a],&tb->album_artist[b]);

  if (x!=0)
    return (GMTrackView::reverse_artist) ? -x : x;


  if (ta->no>tb->no) return 1;
  else if (ta->no<tb->no) return -1;
  return 0;
  }
