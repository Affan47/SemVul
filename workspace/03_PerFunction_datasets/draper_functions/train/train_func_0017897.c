gl_remove_displaylist_fonts()
{
# if HAVE_GL


  fl_font_ = 0;
  fl_size_ = 0;

  for (int j = 0 ; j < FL_FREE_FONT ; ++j)
  {
    Fl_FontSize* past = 0;
    Fl_Fontdesc* s    = fl_fonts + j ;
    Fl_FontSize* f    = s->first;
    while (f != 0) {
      if(f->listbase) {
        if(f == s->first) {
          s->first = f->next;
        }
        else {
          past->next = f->next;
        }


        glDeleteLists(f->listbase, 256);

        Fl_FontSize* tmp = f;
        f = f->next;
        delete tmp;
      }
      else {
        past = f;
        f = f->next;
      }
    }
  }

#endif
}
