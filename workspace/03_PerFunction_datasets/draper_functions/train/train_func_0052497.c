p_setpos(char* text, int* consumed){
	int player; int x; int y;
	char* check = tokenize(text, consumed, "\x3" "iii", &player, &x, &y);
	if (!check) return 0;

	return setpos_cmd(player, x, y);
}
