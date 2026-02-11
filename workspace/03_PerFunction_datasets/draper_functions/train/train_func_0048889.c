bad_for_salt (char c)
{
  switch (c)
    {
    case '0' ... '9':
    case 'A' ... 'Z':
    case 'a' ... 'z':
    case '.': case '/':
      return false;

    default:
      return true;
    }
}
