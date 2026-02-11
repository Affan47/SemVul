rightImage(int id, GemState *state) {
  if(!state)return;
  if(id<0 || id>=6) {
    error("not a valid image-slot %d", id);
  }
  pixBlock*img=NULL;
  state->get(GemState::_PIX, img);

  if(img) {
    if(img->newimage) {
      m_img[id]=&img->image;
    } else {

    }
  }

}
