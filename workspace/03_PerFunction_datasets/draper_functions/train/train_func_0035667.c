awake(plan *ego_, enum wakefulness wakefulness)
{
     P *ego = (P *) ego_;
     X(plan_awake)(ego->cld, wakefulness);

     switch (wakefulness) {
	 case SLEEPY:
	      X(triggen_destroy)(ego->t); ego->t = 0;
	      break;
	 default:
	      ego->t = X(mktriggen)(AWAKE_SQRTN_TABLE, ego->r * ego->m);
	      break;
     }
}
