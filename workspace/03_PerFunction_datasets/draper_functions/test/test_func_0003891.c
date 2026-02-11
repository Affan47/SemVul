str16size(SDL_String16 *pString16)
{
  SDL_Rect Ret = {0, 0, 0, 0};

  if (pString16 && pString16->text && pString16->text != '\0') {
    Uint16 *pStr16 = pString16->text;
    Uint16 c = *pStr16;
    bool new_line = FALSE;
    int w, h;


    while (c != '\0') {
      if (c == 10) {
	new_line = TRUE;
	break;
      }
      pStr16++;
      c = *pStr16;
    }

    if (!((pString16->style & 0x0F) & TTF_STYLE_NORMAL)) {
      TTF_SetFontStyle(pString16->font, (pString16->style & 0x0F));
    }

    if (new_line) {
      int ww, hh, count = 0;
      Uint16 **UniTexts = create_new_line_unistrings(pString16->text);

      w = 0;
      h = 0;
      while (UniTexts[count]) {
        if (TTF_SizeUNICODE(pString16->font, UniTexts[count], &ww, &hh) < 0) {
          do {
	    FC_FREE(UniTexts[count]);
            count++;
	  } while(UniTexts[count]);
          log_error("TTF_SizeUNICODE return ERROR !");
        }
        w = MAX(w, ww);
        h += hh;
        FC_FREE(UniTexts[count]);
        count++;
      }
    } else {
      if (TTF_SizeUNICODE(pString16->font, pString16->text, &w, &h) < 0) {
        log_error("TTF_SizeUNICODE return ERROR !");
      }
    }

    if (!((pString16->style & 0x0F) & TTF_STYLE_NORMAL)) {
      TTF_SetFontStyle(pString16->font, TTF_STYLE_NORMAL);
    }

    Ret.w = w;
    Ret.h = h;
  } else {
    Ret.h = (pString16 ? TTF_FontHeight(pString16->font) : 0);
  }

  return Ret;
}
