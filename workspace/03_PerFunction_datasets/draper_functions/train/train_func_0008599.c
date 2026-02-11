awake(plan *ego_, enum wakefulness wakefulness)
{
     P *ego = (P *) ego_;
     X(plan_awake)(ego->cldt, wakefulness);
     X(plan_awake)(ego->cld_dft, wakefulness);
     X(plan_awake)(ego->cld_ddft, wakefulness);

     switch (wakefulness) {
         case SLEEPY:
              X(triggen_destroy)(ego->t); ego->t = 0;
              break;
         default:
              ego->t = X(mktriggen)(AWAKE_SQRTN_TABLE, ego->r * ego->m);
              break;
     }
}
