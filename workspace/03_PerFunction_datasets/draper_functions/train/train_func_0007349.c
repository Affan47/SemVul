GMT_label_syntax (GMT_LONG indent, GMT_LONG kind)
{


	GMT_LONG i;
	char pad[16];

	pad[0] = '\t';	for (i = 1; i <= indent; i++) pad[i] = ' ';	pad[i] = '\0';
	fprintf (stderr, "%s +a<angle> for annotations at a fixed angle, +an for line-normal, or +ap for line-parallel [Default]\n", pad);
	if (kind == 0) fprintf (stderr, "%s   For +ap, optionally append u for up-hill and d for down-hill cartographic annotations\n", pad);
	fprintf (stderr, "%s +c<dx>[/<dy>] to change the clearance between label and text box [15%%]\n", pad);
	fprintf (stderr, "%s +d turns on debug which draws helper points and lines\n", pad);
	fprintf (stderr, "%s +f followed by desired label font [Default is %ld].\n", pad, gmtdefs.annot_font[0]);
	fprintf (stderr, "%s +g[<color>] for opaque text box [Default is transparent]; optionally give color [white]\n", pad);
	fprintf (stderr, "%s +j<just> to set label justification [Default is CM]\n", pad);
	fprintf (stderr, "%s +k<color> to change color of label text [Default is black]\n", pad);
	if (kind == 1) {
		fprintf (stderr, "%s +l<label> Use this fixed text as the label (quote text if containing spaces).\n", pad);
		fprintf (stderr, "%s +L<d|D|f|h|n|N|x>[<unit>] Sets the label according to the given flag:\n", pad);
		fprintf (stderr, "%s   d Cartesian plot distance; append desired unit c, i, m, or p.\n", pad);
		fprintf (stderr, "%s   D Map distance; append desired unit d, e, k, m, or n.\n", pad);
		fprintf (stderr, "%s   f Label is text after 2nd column the <ffile.d> fixed label location file.\n", pad);
		fprintf (stderr, "%s   h Use multisegment header labels (either in -Lstring or first word).\n", pad);
		fprintf (stderr, "%s   n Use the current multisegment number (starting at 0).\n", pad);
		fprintf (stderr, "%s   N Use current file number / multisegment number (starting at 0/0).\n", pad);
		fprintf (stderr, "%s   x Like h, but scan headers in the <xfile.d> crossing lines instead.\n", pad);
	}
	fprintf (stderr, "%s +n<dx>[/<dy>] to nudge placement of label along line (+N for along x/y axis)\n", pad);
	fprintf (stderr, "%s +o to use rounded rectangular text box [Default is rectangular]\n", pad);
	fprintf (stderr, "%s +p[<pen>] draw outline of textbox  [Default is no outline]; optionally give pen [Default is default pen]\n", pad);
	fprintf (stderr, "%s +r<min_rad> places no labels where radius of curvature < <min_rad> [Default is 0].\n", pad);
	fprintf (stderr, "%s +s followed by desired font size in points [Default is 9 point].\n", pad);
	fprintf (stderr, "%s +u<unit> to append unit to labels; Start with - for no space between annotation and unit.\n", pad);
	if (kind == 0) fprintf (stderr, "%s  If z is appended we use the z-unit from the grdfile. [Default is no unit]\n", pad);
	fprintf (stderr, "%s +v for placing curved text along path [Default is straight]\n", pad);
	fprintf (stderr, "%s +w to set how many (x,y) points to use for angle calculation [Default is 10]\n", pad);
	fprintf (stderr, "%s +=<prefix> to give labels a prefix; Start with - for no space between annotation and prefix.\n", pad);
}
