delete_like_motions(Motion *m, float augment)
{
  Motion **s = &allMotions;
  Motion *n;
  int was_translation = is_translation(m);

  while (*s) {
    if ((*s)->moving_id == m->moving_id


	&& ((*s)->transform == m->transform ||

	    (was_translation && is_translation(*s))) ) {

      if(augment != 0) {


	float scl = augment * ((*s)->timeunit!=0 && m->timeunit!=0
			       ? m->timeunit / (*s)->timeunit : 1);
	m->amount[0] = (1-augment)*m->amount[0] + scl*(*s)->amount[0];
	m->amount[1] = (1-augment)*m->amount[1] + scl*(*s)->amount[1];
	m->amount[2] = (1-augment)*m->amount[2] + scl*(*s)->amount[2];
      }

      n = (*s)->next;
      if((*s)->timeleft)
	apply_motion(*s, 1e10);
      else
	OOGLFree(*s);
      *s = n;
    } else {
      s = &(*s)->next;
    }
  }
}
