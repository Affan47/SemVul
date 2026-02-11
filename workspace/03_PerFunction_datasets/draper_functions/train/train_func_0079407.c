get_col_heading (const char **S, int j, int slopes,
		 int intervals)
{
    if (j == 3 && slopes) {
	return _(S[j+1]);
    } else if (intervals && (j == 1 || j == 2)) {
	return _(S[j+4]);
    } else {
	return _(S[j]);
    }
}
