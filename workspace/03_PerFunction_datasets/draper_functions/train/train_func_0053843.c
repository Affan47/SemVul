FreeRound(Army * att,Army * def, int ass)
{

	AddLine(*(att->leader->name) + " gets a free round of attacks.");


	att->shields.DeleteAll();
	UpdateShields(att);

	def->shields.DeleteAll();
	UpdateShields(def);


	att->round++;


	int alv = def->NumAlive();
	while (att->CanAttack() && def->NumAlive()) {
		int num = getrandom(att->CanAttack());
		int behind;
		Soldier * a = att->GetAttacker(num, behind);
		DoAttack(att->round, a, att, def, behind, ass);
	}


	def->Regenerate(this);
	alv -= def->NumAlive();
	AddLine(*(def->leader->name) + " loses " + alv + ".");
	AddLine("");
	att->Reset();
}
