toLower(std::string array) {
    return std::use_facet<std::ctype<char> >(std::locale()).tolower(&array[0], &array[0] + array.length()) - array.length();
  }
