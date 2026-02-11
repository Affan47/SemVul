update()
  {
    for (unsigned int line=0; line != height; line+=4)
      {
	std::copy(in+line*width,in+(line+1)*width,out+(line*width));
	std::fill(out+(line+1)*width,out+(line+5)*width,0x00000000);
      }
  }
