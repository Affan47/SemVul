PrintCursorNames_ (void)
{
int		i, j, name_length;
static char	nameAA[78][20] = {"X_cursor",           "arrow",
				  "based_arrow_down",   "based_arrow_up",
				  "boat",               "bogosity",
				  "bottom_left_corner", "bottom_right_corner",
				  "bottom_side",        "bottom_tee",
				  "box_spiral",         "center_ptr",
				  "circle",             "clock",
				  "coffee_mug",         "cross",
				  "cross_reverse",      "crosshair",
				  "diamond_cross",      "dot",
				  "dotbox",             "double_arrow",
				  "draft_large",        "draft_small",
				  "draped_box",         "exchange",
				  "fleur",              "gobbler",
				  "gumby",              "hand1",
				  "hand2",              "heart",
				  "icon",               "iron_cross",
				  "left_ptr",           "left_side",
				  "left_tee",           "leftbutton",
				  "ll_angle",           "lr_angle",
				  "man",                "middlebutton",
				  "mouse",              "pencil",
				  "pirate",             "plus",
				  "question_arrow",     "right_ptr",
				  "right_side",         "right_tee",
				  "rightbutton",        "rtl_logo",
				  "sailboat",           "sb_down_arrow",
				  "sb_h_double_arrow",  "sb_left_arrow",
				  "sb_right_arrow",     "sb_up_arrow",
				  "sb_v_double_arrow",  "shuttle",
				  "sizing",             "spider",
				  "spraycan",           "star",
				  "target",             "tcross",
				  "top_left_arrow",     "top_left_corner",
				  "top_right_corner",   "top_side",
				  "top_tee",            "trek",
				  "ul_angle",           "umbrella",
				  "ur_angle",           "watch",
				  "xterm",              "num_glyphs"};

printf ("\n");
printf ("==========================================================\n");
printf ("X11 cursors (hard-coded custom cursor is used as default):\n");
printf ("==========================================================\n");
for (i = 0; i < 78; i++)
	{
	name_length = strlen (nameAA[i]);
	for (j = 0; j < name_length; j++) printf ("%c", nameAA[i][j]);
	if (((i + 1) % 3) == 0) printf ("\n");
	else for (j = name_length; j < 21; j++) printf (" ");
	}
printf ("==========================================================\n");

}
