readDepth(const std::string & fileName,
    cv::Mat1f& depth_img) {
  uint32_t depth_rows = 0, depth_cols = 0;

  std::string input_string;
  std::ifstream infile;

  infile.open(fileName.c_str());
  getline(infile, input_string);

  if (input_string != "P2") {
    std::cout << fileName << ": Wrong image Header ( " << input_string
        << " ) ..." << std::endl;
    return false;
  }

  infile >> depth_cols;
  infile >> depth_rows;

  int maxval;
  infile >> maxval;

  depth_img = cv::Mat1f(depth_rows, depth_cols);

  for( uint32_t y = 0; y < depth_rows; y++ )
  {
    for ( uint32_t x = 0; x < depth_cols; x++ )
    {
      int n;
      if ( infile.eof() )
      {
        std::cout << "ERROR: end-of-file reached too early!" << std::endl;
        exit(-1);
      }
      infile >> n;
      if (n == 0) {
        depth_img(y, x) = std::numeric_limits<float>::quiet_NaN();
      } else {
        depth_img(y, x) = float(n) * 0.001;
      }
    }
  }

  infile.close();

  return true;
}
