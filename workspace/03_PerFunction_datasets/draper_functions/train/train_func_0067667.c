htk_hmm_has_several_arc_on_edge(HTK_HMM_INFO *hmminfo)
{
  HTK_HMM_Data *dt;
  HTK_HMM_Trans *t;
  boolean flag;
  int i;

  for (dt = hmminfo->start; dt; dt = dt->next) {
    t = dt->tr;
    flag = FALSE;
    for (i=0;i<t->statenum;i++) {
      if (t->a[0][i] != LOG_ZERO) {
	if (flag == FALSE) {
	  flag = TRUE;
	} else {
	  jlog("Stat: check_hmm_restriction: an HMM with several arcs from initial state found: \"%s\"\n", dt->name);
	  return (TRUE);
	}
      }
    }
    flag = FALSE;
    for (i=0;i<t->statenum;i++) {
      if (t->a[i][t->statenum-1] != LOG_ZERO) {
	if (flag == FALSE) {
	  flag = TRUE;
	} else {
	  jlog("Stat: check_hmm_restriction: an HMM with several arcs to final state found: \"%s\"\n", dt->name);
	  return (TRUE);
	}
      }
    }
  }

  return FALSE;
}
