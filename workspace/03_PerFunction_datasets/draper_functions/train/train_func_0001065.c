pedwarn_strange_white_space (ch)
     int ch;
{
  switch (ch)
    {
    case '\f': pedwarn ("formfeed in preprocessing directive"); break;
    case '\r': pedwarn ("carriage return in preprocessing directive"); break;
    case '\v': pedwarn ("vertical tab in preprocessing directive"); break;
    default: abort ();
    }
}
