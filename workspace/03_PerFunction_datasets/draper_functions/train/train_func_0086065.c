trial_chance(talk_response response, player *u, npc *p)
{
 talk_trial trial = response.trial;
 int chance = response.difficulty;
 switch (trial) {
  case TALK_TRIAL_LIE:
   chance += u->talk_skill() - p->talk_skill() + p->op_of_u.trust * 3;
   if (u->has_trait(PF_TRUTHTELLER))
    chance -= 40;
   break;

  case TALK_TRIAL_PERSUADE:
   chance += u->talk_skill() - int(p->talk_skill() / 2) +
           p->op_of_u.trust * 2 + p->op_of_u.value;
   if (u->has_trait(PF_GROWL))
    chance -= 25;
   if (u->has_trait(PF_SNARL))
    chance -= 60;
   break;

  case TALK_TRIAL_INTIMIDATE:
   chance += u->intimidation() - p->intimidation() + p->op_of_u.fear * 2 -
           p->personality.bravery * 2;
   if (u->has_trait(PF_TERRIFYING))
    chance += 15;
   if (p->has_trait(PF_TERRIFYING))
    chance -= 15;
   if (u->has_trait(PF_GROWL))
    chance += 15;
   if (u->has_trait(PF_SNARL))
    chance += 30;
   break;

 }

 if (chance < 0)
  return 0;
 if (chance > 100)
  return 100;

 return chance;
}
