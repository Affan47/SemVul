appendHistory(const FXString& search,const FXString& replace,FXuint mode){
  register const char* val;
  register int i;
  if(!search.empty()){
    if(search!=getApp()->reg().readStringEntry(searchgroup,skey[0],FXString::null)){
      for(i=19; i>0; i--){
        if((val=getApp()->reg().readStringEntry(searchgroup,skey[i-1],NULL))!=NULL) getApp()->reg().writeStringEntry(searchgroup,skey[i],val);
        if((val=getApp()->reg().readStringEntry(searchgroup,rkey[i-1],NULL))!=NULL) getApp()->reg().writeStringEntry(searchgroup,rkey[i],val);
        if((val=getApp()->reg().readStringEntry(searchgroup,mkey[i-1],NULL))!=NULL) getApp()->reg().writeStringEntry(searchgroup,mkey[i],val);
        }
      }
    getApp()->reg().writeStringEntry(searchgroup,skey[0],search.text());
    getApp()->reg().writeStringEntry(searchgroup,rkey[0],replace.text());
    getApp()->reg().writeUnsignedEntry(searchgroup,mkey[0],mode);
    }
  }
