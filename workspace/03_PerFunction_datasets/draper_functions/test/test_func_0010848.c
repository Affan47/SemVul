fear_monster(int dir, int plev, bool aware)
{
	int flg = PROJECT_STOP | PROJECT_KILL;
	if(aware) flg |= PROJECT_AWARE;
	return (project_hook(GF_TURN_ALL, dir, plev, flg));
}
