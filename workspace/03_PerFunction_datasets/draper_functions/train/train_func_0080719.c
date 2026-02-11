pop() {


    if (depth_ > 0) {
      depth_ --;
      return margins_[depth_];
    } else return 4;
  }
