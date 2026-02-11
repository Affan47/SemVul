kvu_get_argument_number(int number, const string& arg)
{
  string result;
  vector<string> temp = kvu_get_arguments(arg);
  if (static_cast<int>(temp.size()) >= number) {
    result = temp[number - 1];
  }
  return result;
}
