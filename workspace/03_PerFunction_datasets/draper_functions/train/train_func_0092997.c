ParseFrame(XmtLayoutWidget lw, XmtLayoutInfo *i)
#else
static void ParseFrame(lw, i)
XmtLayoutWidget lw;
XmtLayoutInfo *i;
#endif
{
    int type, linetype;

    i->dummy_constraints.frame_line_type = 1;
    i->dummy_constraints.frame_type = 1;
    type = XmtLayoutFrameBox;

    switch(GetKeyword()) {
    case SHADOWED: linetype = XmtLayoutFrameShadowIn; break;
    default:
    case ETCHED:   linetype = XmtLayoutFrameEtchedIn; break;
    case LINE:
    case BOXED:    linetype = XmtLayoutFrameSingleLine; break;
    case DOUBLELINE:
    case DOUBLEBOXED: linetype = XmtLayoutFrameDoubleLine; break;
    }
    ConsumeToken();

    if (GetToken() == XmtLexerKeyword) {
	if (GetKeyword() == OUT) {
	    if (linetype == XmtLayoutFrameShadowIn)
		linetype = XmtLayoutFrameShadowOut;
	    else if (linetype == XmtLayoutFrameEtchedIn)
		linetype = XmtLayoutFrameEtchedOut;
	    ConsumeToken();
	}
	else if (GetKeyword() == IN) ConsumeToken();
    }
    i->constraints.frame_line_type = linetype;

    if (GetToken() == XmtLexerKeyword) {
	switch(GetKeyword()) {
	case LEFT:
	    type = XmtLayoutFrameLeft; break;
	case RIGHT:
	    type = XmtLayoutFrameRight; break;
	case TOP:
	    type = XmtLayoutFrameTop; break;
	case BOTTOM:
	    type = XmtLayoutFrameBottom; break;
	}
	if (type != XmtLayoutFrameBox) ConsumeToken();
    }

    i->constraints.frame_type = type;

    if (GetToken() == XmtLexerKeyword) {
	i->dummy_constraints.frame_position = 1;
	if (GetKeyword() == INSIDE)
	    i->constraints.frame_position = XmtLayoutFrameInside;
	else if (GetKeyword() == OUTSIDE)
	    i->constraints.frame_position = XmtLayoutFrameOutside;
	else if (GetKeyword() == THROUGH)
	    i->constraints.frame_position = XmtLayoutFrameThrough;
	else
	    i->dummy_constraints.frame_position = 0;

	if (i->dummy_constraints.frame_position) ConsumeToken();
    }

    if (GetToken() == XmtLexerInteger) {
	i->dummy_constraints.frame_margin = 1;
	i->constraints.frame_margin = GetIntValue();
	ConsumeToken();
	if (GetToken() == XmtLexerInteger) {
	    i->dummy_constraints.frame_thickness = 1;
	    i->constraints.frame_thickness = GetIntValue();
	    ConsumeToken();
	}
    }
}
