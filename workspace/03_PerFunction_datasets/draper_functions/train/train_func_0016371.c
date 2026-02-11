CleanTestOutput(std::string& output, size_t length)
{
  if(!length || length >= output.size() ||
     output.find("CTEST_FULL_OUTPUT") != output.npos)
    {
    return true;
    }


  char const* const begin = output.c_str();
  char const* const end = begin + output.size();
  char const* const truncate = begin + length;
  char const* current = begin;
  while(current < truncate)
    {
    unsigned int ch;
    if(const char* next = cm_utf8_decode_character(current, end, &ch))
      {
      if(next > truncate)
        {
        break;
        }
      current = next;
      }
    else
      {
      ++current;
      }
    }
  output = output.substr(0, current - begin);


  cmOStringStream msg;
  msg << "...\n"
    "The rest of the test output was removed since it exceeds the threshold "
    "of " << length << " bytes.\n";
  output += msg.str();
  return true;
}
