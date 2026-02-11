expulsion(seal)
boolean seal;
{
    branch *br;
    d_level *dest;
    struct trap *t;
    int portal_flag;

    br = dungeon_branch("The Quest");
    dest = (br->end1.dnum == u.uz.dnum) ? &br->end2 : &br->end1;
    portal_flag = u.uevent.qexpelled ? 0 :
		  !seal ? 1 : -1;
    schedule_goto(dest, FALSE, FALSE, portal_flag, (char *)0, (char *)0);
    if (seal) {
	int reexpelled = u.uevent.qexpelled;
	u.uevent.qexpelled = 1;


	for (t = ftrap; t; t = t->ntrap)
	    if (t->ttyp == MAGIC_PORTAL) break;
	if (t) deltrap(t);
	else if (!reexpelled) impossible("quest portal already gone?");
    }
}
