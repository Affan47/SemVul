drawElementBackground(XmIconListWidget _ilw, int _nelement, GC _gc)
#else
static void drawElementBackground(_ilw, _nelement, _gc)
XmIconListWidget _ilw;
int _nelement;
GC _gc;
#endif
{
   Position y;
   Position x;

   if (_nelement < START_ROW(_ilw))
      return;

   y = _nelement * FULL_EL_HEIGHT(_ilw) + HT(_ilw);
   x = HT(_ilw);

   XFillRectangle(XtDisplay(_ilw), XtWindow(_ilw), _gc,
            x, y, WIDTH(_ilw)-2*HT(_ilw), FULL_EL_HEIGHT(_ilw)-2*HT(_ilw));
}
