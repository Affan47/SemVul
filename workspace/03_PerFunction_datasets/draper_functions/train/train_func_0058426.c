getToken(StringRef Source,
                                               StringRef Delimiters) {

  StringRef::size_type Start = Source.find_first_not_of(Delimiters);


  StringRef::size_type End = Source.find_first_of(Delimiters, Start);

  return std::make_pair(Source.slice(Start, End), Source.substr(End));
}
