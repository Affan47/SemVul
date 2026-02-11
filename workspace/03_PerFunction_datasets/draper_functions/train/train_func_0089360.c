substitute(string pattern, string src,
                        string replacement, string & dest, bool global)
{
  string src_left, src_right, dest_right, result;
  int differ, index=0, de=0;


  if (global)
    {
      result=src;
      do {
        src_left=result.substr(0,index);
        src_right=result.substr(index);
        differ=substitute_local(pattern, src_right,
                                replacement, dest_right, de);
        result=src_left+dest_right;
        index+=de;
      } while (differ);
      dest=result;
    }
  else
    substitute_local(pattern, src, replacement, dest, de);
}
