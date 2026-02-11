SplitIntoLines(const string &input) {
  vector<string> lines;

  string::size_type begin_index = 0;
  string::size_type input_len = input.length();

  while (1) {
    string::size_type end_index = input.find_first_of('\n', begin_index);
    if (end_index == string::npos) {
        lines.push_back(input.substr(begin_index));
      break;
    }
    lines.push_back(input.substr(begin_index, (end_index - begin_index)));
    begin_index = end_index + 1;
    if (begin_index >= input_len)
      break;
  }
  return lines;
}
