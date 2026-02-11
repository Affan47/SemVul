plhrsh(PLINT ch, PLINT x, PLINT y)
{
EscText args;
int idx;
PLUNICODE unicode_char;


  if ((plsc->dev_text)&&(plsc->dev_unicode)&&(!plsc->dev_hrshsym))
    {
      idx=plhershey2unicode(ch);
      unicode_char=hershey_to_unicode_lookup_table[idx].Unicode;


      if ((unicode_char==0)||(idx==-1))
        {
#ifndef TEST_FOR_MISSING_GLYPHS
          plhrsh2(ch, x, y);
#endif
        }
      else
        {
	  PLUNICODE  plhrsh_unicode_buffer[3], fci;
	  PLFLT xform[] = {1.0, 0.0, 0.0, 1.0};
	  unsigned char esc;
          args.unicode_char=unicode_char;
          args.font_face=hershey_to_unicode_lookup_table[idx].Font;
          args.base = 1;
          args.just = .5;
          args.xform = 0;
          args.x = x;
          args.y = y;
	  args.string=NULL;

	  plgesc(&esc);
	  args.xform = xform;
	  args.unicode_array_len=2;

	  plgfci(&fci);
	  plP_hex2fci(PL_FCI_SYMBOL, PL_FCI_FAMILY, &fci);
	  plhrsh_unicode_buffer[0] = fci;
	  plhrsh_unicode_buffer[1] = unicode_char;


	  if (unicode_char == esc) {
	     args.unicode_array_len=3;
	     plhrsh_unicode_buffer[2] = unicode_char;
	  }


	  args.unicode_array=&plhrsh_unicode_buffer[0];

          plsc->original_chrht=plsc->chrht;
          plsc->original_chrdef=plsc->chrdef;
          plsc->chrht=plsc->symht;
          plsc->chrdef=plsc->symdef;

          plP_esc(PLESC_HAS_TEXT, &args);

          plsc->chrht=plsc->original_chrht;
          plsc->chrdef=plsc->original_chrdef;
        }

    }
  else
    {
       plhrsh2(ch, x, y);
    }
}
