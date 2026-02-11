moreShild(){
  float add = 1;
  this->maxShild += add;
  if (maxShild > 120)
    maxShild = 120;

  this->wappon = (INITIALWAPPON*INITIALSHILD)/maxShild;

}
