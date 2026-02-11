decode(std::vector<unsigned char>& out, unsigned& w, unsigned& h, const std::vector<unsigned char>& in, unsigned colorType, unsigned bitDepth)
  {
    return decode(out, w, h, in.empty() ? 0 : &in[0], (unsigned)in.size(), colorType, bitDepth);
  }
