_pcre_xclass(int c, const uschar *data)
{
int t;
BOOL negated = (*data & XCL_NOT) != 0;


if (c < 256)
  {
  if ((*data & XCL_MAP) != 0 && (data[1 + c/8] & (1 << (c&7))) != 0)
    return !negated;
  }


if ((*data++ & XCL_MAP) != 0) data += 32;

while ((t = *data++) != XCL_END)
  {
  int x, y;
  if (t == XCL_SINGLE)
    {
    GETCHARINC(x, data);
    if (c == x) return !negated;
    }
  else if (t == XCL_RANGE)
    {
    GETCHARINC(x, data);
    GETCHARINC(y, data);
    if (c >= x && c <= y) return !negated;
    }

#ifdef SUPPORT_UCP
  else
    {
    const ucd_record * prop = GET_UCD(c);

    switch(*data)
      {
      case PT_ANY:
      if (t == XCL_PROP) return !negated;
      break;

      case PT_LAMP:
      if ((prop->chartype == ucp_Lu || prop->chartype == ucp_Ll || prop->chartype == ucp_Lt) ==
          (t == XCL_PROP)) return !negated;
      break;

      case PT_GC:
      if ((data[1] == _pcre_ucp_gentype[prop->chartype]) == (t == XCL_PROP)) return !negated;
      break;

      case PT_PC:
      if ((data[1] == prop->chartype) == (t == XCL_PROP)) return !negated;
      break;

      case PT_SC:
      if ((data[1] == prop->script) == (t == XCL_PROP)) return !negated;
      break;


      default:
      return FALSE;
      }

    data += 2;
    }
#endif
  }

return negated;
}
