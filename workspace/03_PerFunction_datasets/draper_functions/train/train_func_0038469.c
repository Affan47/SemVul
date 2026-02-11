GWEN_Widget_Flags_fromString(const char *s){
  uint32_t fl=0;

  if (s && *s) {
    char *copy;
    char *p;

    copy=strdup(s);
    p=copy;

    while(*p) {
      char *wstart;


      while(*p && isspace(*p))
	p++;

      wstart=p;


      while(*p && !(isspace(*p) || *p==','))
	p++;
      if (*p)

	*(p++)=0;


      if (strcasecmp(wstart, "fillX")==0)
        fl|=GWEN_WIDGET_FLAGS_FILLX;
      else if (strcasecmp(wstart, "fillY")==0)
	fl|=GWEN_WIDGET_FLAGS_FILLY;
      else if (strcasecmp(wstart, "readOnly")==0)
	  fl|=GWEN_WIDGET_FLAGS_READONLY;
      else if (strcasecmp(wstart, "password")==0)
	  fl|=GWEN_WIDGET_FLAGS_PASSWORD;
      else if (strcasecmp(wstart, "default")==0)
	fl|=GWEN_WIDGET_FLAGS_DEFAULT_WIDGET;
      else if (strcasecmp(wstart, "decorShrinkable")==0)
	fl|=GWEN_WIDGET_FLAGS_DECOR_SHRINKABLE;
      else if (strcasecmp(wstart, "decorStretchable")==0)
	fl|=GWEN_WIDGET_FLAGS_DECOR_STRETCHABLE;
      else if (strcasecmp(wstart, "decorMinimize")==0)
	fl|=GWEN_WIDGET_FLAGS_DECOR_MINIMIZE;
      else if (strcasecmp(wstart, "decorMaximize")==0)
	fl|=GWEN_WIDGET_FLAGS_DECOR_MAXIMIZE;
      else if (strcasecmp(wstart, "decorClose")==0)
	fl|=GWEN_WIDGET_FLAGS_DECOR_CLOSE;
      else if (strcasecmp(wstart, "decorMenu")==0)
	fl|=GWEN_WIDGET_FLAGS_DECOR_MENU;
      else if (strcasecmp(wstart, "fixedWidth")==0)
	fl|=GWEN_WIDGET_FLAGS_FIXED_WIDTH;
      else if (strcasecmp(wstart, "fixedHeight")==0)
	fl|=GWEN_WIDGET_FLAGS_FIXED_HEIGHT;
      else if (strcasecmp(wstart, "equalWidth")==0)
	fl|=GWEN_WIDGET_FLAGS_EQUAL_WIDTH;
      else if (strcasecmp(wstart, "equalHeight")==0)
	fl|=GWEN_WIDGET_FLAGS_EQUAL_HEIGHT;
      else if (strcasecmp(wstart, "justifyLeft")==0)
	fl|=GWEN_WIDGET_FLAGS_JUSTIFY_LEFT;
      else if (strcasecmp(wstart, "justifyRight")==0)
	fl|=GWEN_WIDGET_FLAGS_JUSTIFY_RIGHT;
      else if (strcasecmp(wstart, "justifyTop")==0)
	fl|=GWEN_WIDGET_FLAGS_JUSTIFY_TOP;
      else if (strcasecmp(wstart, "justifyBottom")==0)
	fl|=GWEN_WIDGET_FLAGS_JUSTIFY_BOTTOM;
      else if (strcasecmp(wstart, "justifyCenterX")==0)
	fl|=GWEN_WIDGET_FLAGS_JUSTIFY_CENTERX;
      else if (strcasecmp(wstart, "justifyCenterY")==0)
	fl|=GWEN_WIDGET_FLAGS_JUSTIFY_CENTERY;
      else if (strcasecmp(wstart, "noWordWrap")==0)
	fl|=GWEN_WIDGET_FLAGS_NO_WORDWRAP;
    }
  }

  return fl;
}
