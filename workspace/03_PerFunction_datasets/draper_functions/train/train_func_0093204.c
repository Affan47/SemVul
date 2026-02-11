operator=(win_background & wb)
{
  destroy();
  background_template_=new image();
  *background_template_=*(wb.background_template_);
  background_=new image();
  background_->set_mask(false);
  background_brightness_= new image();
  background_brightness_->set_mask(true);

  update();

  return *this;

}
