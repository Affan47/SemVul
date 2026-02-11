Run() {
    while (running()) {

      values_[width_/2][height_/2]++;
      updateValues();

      for (int x=0; x<width_; ++x) {
        for (int y=0; y<height_; ++y) {
          switch (values_[x][y]) {
            case 0:
              canvas()->SetPixel(x, y, 0, 0, 0);
              break;
            case 1:
              canvas()->SetPixel(x, y, 0, 0, 200);
              break;
            case 2:
              canvas()->SetPixel(x, y, 0, 200, 0);
              break;
            case 3:
              canvas()->SetPixel(x, y, 150, 100, 0);
              break;
            default:
              canvas()->SetPixel(x, y, 200, 0, 0);
          }
        }
      }
      usleep(delay_ms_ * 1000);
    }
  }
