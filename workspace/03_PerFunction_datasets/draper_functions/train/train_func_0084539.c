onDNDDrop(FXObject* sender,FXSelector sel,void* ptr){
  FXString dropfiles,filesrc,filedst,url;
  FXint beg,end;


  stopAutoScroll();


  if(FXTreeList::onDNDDrop(sender,sel,ptr)) return 1;


  if(getDNDData(FROM_DRAGNDROP,urilistType,dropfiles)){


    dropFinished(DRAG_ACCEPT);


    for(beg=0; beg<dropfiles.length(); beg=end+2){
      if((end=dropfiles.find_first_of("\r\n",beg))<0) end=dropfiles.length();


      url=dropfiles.mid(beg,end-beg);


      filesrc=FXURL::decode(FXURL::fileFromURL(url));


      filedst=dropdirectory+PATHSEPSTRING+FXPath::name(filesrc);

      if(dropaction==DRAG_MOVE){
        FXTRACE((100,"Moving file: %s to %s\n",filesrc.text(),filedst.text()));
        if(!FXFile::moveFiles(filesrc,filedst)) getApp()->beep();
        }
      else if(dropaction==DRAG_COPY){
        FXTRACE((100,"Copying file: %s to %s\n",filesrc.text(),filedst.text()));
        if(!FXFile::copyFiles(filesrc,filedst)) getApp()->beep();
        }
      else if(dropaction==DRAG_LINK){
        FXTRACE((100,"Linking file: %s to %s\n",filesrc.text(),filedst.text()));
        if(!FXFile::symlink(filesrc,filedst)) getApp()->beep();
        }
      }
    return 1;
    }

  return 0;
  }
