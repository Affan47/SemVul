show_point(int n, int true_color)
{
    if (!true_color)
	R_standard_color(ORANGE);
    else if (group.points.status[n])
	R_standard_color(GREEN);
    else
	R_standard_color(RED);

    display_one_point(VIEW_MAP1, group.points.e1[n], group.points.n1[n]);

    return 0;
}
