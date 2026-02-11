get_exp_value()
{
   int_type value = 0;
   int sign = 1;

   if (curtok == '!') {
      curtok = get_onetok(SKIP_SPACE);
      return !get_exp_value();
   }
   if (curtok == '~') {
      curtok = get_onetok(SKIP_SPACE);
      return ~get_exp_value();
   }

   while (curtok == '+' || curtok == '-') {
      if (curtok == '-') sign = -sign;
      curtok = get_onetok(SKIP_SPACE);
   }

   if (curtok == TK_NUM) {
      value = strtoul(curword, (void*)0, 0);
      curtok = get_onetok(SKIP_SPACE);
   } else if (curtok == TK_QUOT) {
      value = curword[1];
      if (value == '\\') {
	 if (curword[2] >= '0' && curword[2] <= '7') {
	    value = curword[2] - '0';
	    if (curword[3] >= '0' && curword[3] <= '7') {
	       value = (value<<3) + curword[3] - '0';
	       if (curword[4] >= '0' && curword[4] <= '7') {
		  value = (value<<3) + curword[4] - '0';
	       }
	    }
	 } else switch(curword[2]) {
	    case 'n': value = '\n'; break;
	    case 'f': value = '\f'; break;
	    case 't': value = '\t'; break;
	    default:  value = curword[2]; break;
	 }
      }
#ifdef NATIVE_CPP
      value = (char) value;
#elif SIGNED_CHAR
      value = (signed char) value;
#else
      value = (unsigned char) value;
#endif
      curtok = get_onetok(SKIP_SPACE);
   } else if (curtok == TK_WORD) {
      value = 0;
      if (strcmp("defined", curword) == 0) {
	 curtok = gettok_nosub();
	 if (curtok == '(' && gettok_nosub() != TK_WORD)
	    cerror("'defined' keyword requires argument");
	 else {
	    value = (read_entry(0, curword) != 0);
	    if (curtok == '(' && gettok_nosub() != ')')
	       cerror("'defined' keyword requires closing ')'");
	    else
	       curtok = get_onetok(SKIP_SPACE);
	 }
      }
      else
	 curtok = get_onetok(SKIP_SPACE);

   } else if (curtok == '(') {
      value = get_expression(0);
      if (curtok == ')')
	 curtok = get_onetok(SKIP_SPACE);
      else {
	 curtok = '$';
	 cerror("Expected ')'");
      }
   }

   return sign<0 ? -value: value;
}
