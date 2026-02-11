sleep_monster(int dir, bool aware)
{
	int flg = PROJECT_STOP | PROJECT_KILL;
	if(aware) flg |= PROJECT_AWARE;
	return (project_hook(GF_OLD_SLEEP, dir, p_ptr->lev, flg));
}
