mafSlice(const std::vector<std::string>& maf,
				  unsigned alnBeg, unsigned alnEnd) {
  std::vector<std::string> out;
  std::string a, b, c, d, e, f;
  for (unsigned i = 0; i < maf.size(); ++i) {
    const std::string& line = maf[i];
    std::istringstream iss(line);
    if (line[0] == 's') {
      unsigned x;
      iss >> a >> b >> x >> c >> d >> e >> f;
      unsigned beg = x + seqPosFromAlnPos(alnBeg, f);
      unsigned end = x + seqPosFromAlnPos(alnEnd, f);
      unsigned len = end - beg;
      std::ostringstream oss;
      oss << a << ' ' << b << ' ' << beg << ' ' << len << ' '
          << d << ' ' << e << ' ' << f.substr(alnBeg, alnEnd - alnBeg);
      out.push_back(oss.str());
    } else if (line[0] == 'q') {
      iss >> a >> b >> c;
      out.push_back(a + ' ' + b + ' ' + c.substr(alnBeg, alnEnd - alnBeg));
    } else if (line[0] == 'p') {
      iss >> a >> b;
      out.push_back(a + ' ' + b.substr(alnBeg, alnEnd - alnBeg));
    }
  }
  return out;
}
