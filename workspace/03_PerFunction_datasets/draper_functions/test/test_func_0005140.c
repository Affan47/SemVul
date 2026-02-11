p_hudtxt2(char* text, int* consumed){
	int player; int id; char* txt; int x; int y; int align;
	char* check = tokenize(text, consumed, "\x6" "iisiii", &player, &id, &txt, &x, &y, &align);
	if (!check) return 0;

	return hudtxt2_cmd(player, id, txt, x, y, align);
}
