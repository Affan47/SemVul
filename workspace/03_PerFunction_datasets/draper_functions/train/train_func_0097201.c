xdefinecolor(const std::string& model,
				   const std::string& name,
				   double d1, double d2,
				   double d3, double d4) const
  {
    std::stringstream obuf;
    obuf << "\\xdefinecolor{" << name << "}{cmyk}{"
	 << d1 << "," << d2 << "," << d3 << "," << d4 << "}%"
	 << std::endl;

    return obuf.str();
  }
