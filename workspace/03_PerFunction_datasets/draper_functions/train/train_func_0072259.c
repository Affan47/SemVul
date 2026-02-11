configure_next_name(int iMask){
  if( iMask & CONFIGSET_OLDFORMAT ){
    while( iConfig<count(aConfig) ){
      if( aConfig[iConfig].groupMask & iMask ){
        return aConfig[iConfig++].zName;
      }else{
        iConfig++;
      }
    }
  }else{
    if( iConfig==0 && (iMask & CONFIGSET_ALL)==CONFIGSET_ALL ){
      iConfig = count(aGroupName);
      return "/all";
    }
    while( iConfig<count(aGroupName)-1 ){
      if( aGroupName[iConfig].groupMask & iMask ){
        return aGroupName[iConfig++].zName;
      }else{
        iConfig++;
      }
    }
  }
  return 0;
}
