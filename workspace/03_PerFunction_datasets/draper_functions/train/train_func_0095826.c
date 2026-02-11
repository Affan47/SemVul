PrintFstInfo(const FstClass &f, bool test_properties,
                  const string &arc_filter, const string &info_type,
                  bool pipe, bool verify) {
  InfoArgs args(f, test_properties, arc_filter, info_type, pipe, verify);

  Apply<Operation<InfoArgs> >("PrintFstInfo", f.ArcType(), &args);
}
