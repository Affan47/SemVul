ps_printTitle(float boundOx, float boundOy, float boundW, float boundH, char *theTitle, char *fontName, FILE *tbp)
{
    int startXpoint, startYpoint, startsize, minsize;
    int titleBoxHeight;
    int lengthlimit;

    startXpoint = (int)(boundOx + page_margins[currentMarginIndex][MARGIN_RIGHT]);
    startYpoint = (int)(boundOy + page_margins[currentMarginIndex][MARGIN_TITLE]);
    titleBoxHeight = (int)(page_margins[currentMarginIndex][MARGIN_BOTTOM] - page_margins[currentMarginIndex][MARGIN_TITLE]);

    if (titleBoxHeight > 0) {

	startsize = (int)(MYMIN(TEXT_START_SIZE, titleBoxHeight));
	minsize = (int)(TEXT_MIN_SIZE);

	lengthlimit = (int)(boundW -					\
			    page_margins[currentMarginIndex][MARGIN_LEFT] - \
			    startXpoint);

	sprintf(errMsg,
		"box: (boundOx=%g, boundOy=%g, boundW=%g, boundH=%g);\n"
		"startXpoint=%d, startYpoint= %d\n",
		boundOx, boundOy, boundW, boundH, startXpoint, startYpoint);
	myDebug(errMsg);


	myDebug("Writing title");
	fprintf(tbp, "\n%%%% Small ps program to write title at bottom of page\n");
	fprintf(tbp, "/startpoint {%d %d} def\n", startXpoint, startYpoint);
	fprintf(tbp, "/startsize %d def\n", startsize);
	fprintf(tbp, "/minsize %d def\n", minsize);
	fprintf(tbp, "/myfont {/%s} def\n", fontName);
	fprintf(tbp, "/lengthlimit %d def\n", lengthlimit);
	fprintf(tbp, "/mytext (%s) def\n\n", theTitle);


	fprintf(tbp, "myfont findfont startsize scalefont setfont\n");
	fprintf(tbp, "startsize -1 minsize {\n");
	fprintf(tbp, "    /newsize exch def\n");
	fprintf(tbp, "    /textlength mytext stringwidth pop def\n");
	fprintf(tbp, "    textlength lengthlimit le {\n");
	fprintf(tbp, "        exit\n");
	fprintf(tbp, "    } {\n");
	fprintf(tbp, "        myfont newsize selectfont\n");
	fprintf(tbp, "    } ifelse\n");
	fprintf(tbp, "} for\n\n");
	fprintf(tbp, "lengthlimit textlength sub 2 div\n");
	fprintf(tbp, "startpoint pop add\n");
	fprintf(tbp, "startpoint exch pop\n");
	fprintf(tbp, "moveto\n");
	fprintf(tbp, "mytext show");
    } else {
	myDebug("Title not printed because margins are too tight\n");
    }

    return;
}
