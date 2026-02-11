awake(plan *ego_, enum wakefulness wakefulness)
{
     P *ego = (P *) ego_;

     X(plan_awake)(ego->cldf, wakefulness);

     switch (wakefulness) {
	 case SLEEPY:
	      X(ifree0)(ego->w); ego->w = 0;
	      X(ifree0)(ego->W); ego->W = 0;
	      break;
	 default:
	      A(!ego->w);
	      mktwiddle(wakefulness, ego);
	      break;
     }
}
