scaleToSize(FXImage *image,FXint size,FXint qual) const {
  if(image){
    if((image->getWidth()>size) || (image->getHeight()>size)){
      if(image->getWidth()>image->getHeight()){
        image->scale(size,(size*image->getHeight())/image->getWidth(),qual);
        }
      else{
        image->scale((size*image->getWidth())/image->getHeight(),size,qual);
        }
      }
    }
  return image;
  }
