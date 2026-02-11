NormalRound(int round,Army * a,Army * b)
{

    AddLine(AString("Round ") + round + ":");


    UpdateShields(a);
    UpdateShields(b);


    a->round++;
    b->round++;
    int aalive = a->NumAlive();
    int aialive = aalive;
    int balive = b->NumAlive();
    int bialive = balive;
    int aatt = a->CanAttack();
    int batt = b->CanAttack();


    while (aalive && balive && (aatt || batt))
    {
        int num = getrandom(aatt + batt);
        int behind;
        if (num >= aatt)
        {
            num -= aatt;
            Soldier * s = b->GetAttacker(num, behind);
            DoAttack(b->round, s, b, a, behind);
        }
        else
        {
            Soldier * s = a->GetAttacker(num, behind);
            DoAttack(a->round, s, a, b, behind);
        }
        aalive = a->NumAlive();
        balive = b->NumAlive();
        aatt = a->CanAttack();
        batt = b->CanAttack();
    }


	a->Regenerate(this);
	b->Regenerate(this);
    aialive -= aalive;
    AddLine(*(a->leader->name) + " loses " + aialive + ".");
    bialive -= balive;
    AddLine(*(b->leader->name) + " loses " + bialive + ".");
    AddLine("");
    a->Reset();
    b->Reset();
}
