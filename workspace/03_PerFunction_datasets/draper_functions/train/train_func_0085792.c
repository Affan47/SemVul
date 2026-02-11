ctx_print(void)
{

    Ctx_Lock++;


    if (Ctx_Valid_Level < Ctx_Reported_Level) {
	if (Ctx_Reported_Level != Ctx_Valid_Level + 1)
	    _db_print("ctx: exit levels from %2d down to %2d\n",
		Ctx_Reported_Level, Ctx_Valid_Level + 1);
	else
	    _db_print("ctx: exit level %2d\n", Ctx_Reported_Level);
	Ctx_Reported_Level = Ctx_Valid_Level;
    }

    while (Ctx_Reported_Level < Ctx_Current_Level) {
	Ctx_Reported_Level++;
	Ctx_Valid_Level++;
	_db_print("ctx: enter level %2d: '%s'\n", Ctx_Reported_Level,
	    ctx_get_descr(Ctx_Reported_Level));
    }

    Ctx_Lock--;
}
