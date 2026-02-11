_parse_signature(const string &signature, string &type, unsigned int &i, bool only_once = false)
{


  for (; i < signature.length(); ++i)
  {
    switch (signature[i])
    {
    case 'a':
    {
      switch (signature[++i])
      {
      case '{':
      {
        type += "std::map< ";
        ++i;
        _parse_signature(signature, type, i);
        type += " >";

        break;
      }
      case '(':
      {
        type += "std::vector< ::DBus::Struct< ";
        ++i;
        _parse_signature(signature, type, i);
        type += " > >";

        break;
      }
      default:
      {
        type += "std::vector< ";
        _parse_signature(signature, type, i, true);

        type += " >";

        break;
      }
      }
      break;
    }
    case '(':
    {
      type += "::DBus::Struct< ";
      ++i;

      _parse_signature(signature, type, i);

      type += " >";
      break;
    }
    case ')':
    case '}':
    {
      return;
    }
    default:
    {
      const char *atom = atomic_type_to_string(signature[i]);
      if (!atom)
      {
        cerr << "invalid signature" << endl;
        exit(-1);
      }
      type += atom;

      break;
    }
    }

    if (only_once)
      return;

    if (i + 1 < signature.length() && signature[i + 1] != ')' && signature[i + 1] != '}')
    {
      type += ", ";
    }
  }
}
