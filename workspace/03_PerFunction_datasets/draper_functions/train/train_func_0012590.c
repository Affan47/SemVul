gm_convert_filenames_to_uri(const FXStringList & filenames,FXString & uri){
  if (filenames.no()) {
    uri=GMURL::fileToURL(filenames[0]);
    for (FXint i=1;i<filenames.no();i++){
      uri+="\r\n";
      uri+=GMURL::fileToURL(filenames[i]);
      }
    }
  }
