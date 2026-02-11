show_trim (string s)
{
  cerr << "Trimming '" << s << "': spaces (" << trim (s)
       << "), underscores (" << trim (s, TRIM_UNDERSCORE)
       << "), braces (" << trim (s, TRIM_BRACE) << ").\n";


}
