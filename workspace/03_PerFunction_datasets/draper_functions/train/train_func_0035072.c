forwcursor(x)
int x;
{
	while (win_x < x) {
		VOID_C XXputch(' ');
		win_x++;
	}
}
