TTYput(ECHAR c)
{
    Screen[ScreenCount] = c;
    if (++ScreenCount >= ScreenSize - 1) {
	ScreenSize += SCREEN_INC;
	RENEW(Screen, char, ScreenSize);
    }
}
