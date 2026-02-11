check (char *word)
{
  if (!word) {
    puts ("Use `--check=WORD' where WORD can be:");
    puts ("intro	run the intro");
    puts ("demo		run a demo");
    return true;
  }
  if (!strcasecmp (word, "intro"))
    check_what = check_intro;
  else if (!strcasecmp (word, "demo"))
    check_what = check_demo;
  else

    return check (0);
  return false;
}
