getColumnData(FXint type,FXString &text,FXuint & justify,FXint & max) const{
  const FXString * textptr;
  justify=COLUMN_JUSTIFY_NORMAL;
  switch(type){
    case HEADER_QUEUE         : text.format("%d",queue);
                                textptr=&text;
                                justify=COLUMN_JUSTIFY_LEFT_RIGHT_ALIGNED;
                                max=GMDBTrackItem::max_queue;
                                break;

    case HEADER_TRACK         : if (GMTRACKNO((FXuint)(FXuval)no)>0) {
                                  text.format("%d",GMTRACKNO((FXuint)(FXuval)no));
                                  textptr=&text;
                                  justify=COLUMN_JUSTIFY_LEFT_RIGHT_ALIGNED;
                                  max=GMDBTrackItem::max_trackno;
                                  }
                                else {
                                  textptr=NULL;
                                  }
                                break;

    case HEADER_DISC          : if (GMDISCNO((FXuint)(FXuval)no)>0) {
                                  text.format("%d",GMDISCNO((FXuint)(FXuval)no));
                                  textptr=&text;
                                  }
                                else {
                                  textptr=NULL;
                                  }
                                break;

    case HEADER_TITLE         : textptr = &title;  			break;
    case HEADER_ALBUM         : textptr = &album;  			break;
    case HEADER_ARTIST        : textptr = &artist;  		break;
    case HEADER_ALBUM_ARTIST  : textptr = &album_artist;  		break;
    case HEADER_GENRE         : textptr = &genre;    	  break;
    case HEADER_YEAR          :

                                if (year>0) {text.format("%d",year); textptr=&text; } else textptr=NULL; break;
    case HEADER_TIME          :
                                text.format("%d:%.2d",time/60,time%60);
                                textptr=&text;
                                justify=COLUMN_JUSTIFY_CENTER_RIGHT_ALIGNED;
                                max=GMDBTrackItem::max_time;
                                break;
    default							      : textptr=NULL;			 			break;
    }
  return textptr;
  }
