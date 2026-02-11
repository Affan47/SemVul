iseuchiragana(const guchar *buff){
	g_assert(buff != NULL);

	if((buff[0] == 0xa4) &&
	   (buff[1] >= 0xa1) && (buff[1] <= 0xf3))
		return(TRUE);
	return(FALSE);
}
