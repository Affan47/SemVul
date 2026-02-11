ParseSpace(XmtLayoutWidget lw, XmtLayoutLocalInfo *li)
#else
static void ParseSpace(lw, li)
XmtLayoutWidget lw;
XmtLayoutLocalInfo *li;
#endif
{
    switch(GetKeyword()) {
    case EVEN:
    case EVENSPACED:
	li->space_type = XmtLayoutSpaceEven;
	break;
    case LREVENSPACED:
	li->space_type = XmtLayoutSpaceLREven;
	break;
    case INTERVALSPACED:
	li->space_type = XmtLayoutSpaceInterval;
	break;
    case LCRSPACED:
	li->space_type = XmtLayoutSpaceLCR;
	break;
    case LTABBED:
	li->space_type = XmtLayoutSpaceLTabbed;
	break;
    case CTABBED:
	li->space_type = XmtLayoutSpaceCTabbed;
	break;
    case RTABBED:
	li->space_type = XmtLayoutSpaceRTabbed;
	break;
    }

    if (NextToken() == XmtLexerInteger)
	li->space = ParsePixelSize(lw);

    if (GetToken() == XmtLexerPlus) {
	if (NextToken() != XmtLexerInteger)
	    XmtWarningMsg("XmtLayout", "space0",
			  "Widget '%s':\n\tinteger expected following '+' in space specification",
			  XtName((Widget)lw));
	else{
	    li->space_stretch = GetIntValue();

	    if (NextToken() == XmtLexerSlash) {
		if (NextToken() != XmtLexerInteger)
		    XmtWarningMsg("XmtLayout", "space1",
				  "Widget '%s':\n\tinteger expected following '/' in space specification",
				  XtName((Widget)lw));
		else {
		    li->item_stretch = GetIntValue();
		    ConsumeToken();
		}
	    }
	}
    }
}
