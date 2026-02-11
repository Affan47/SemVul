apply_stage3 (bool *mergedp, Chimera_T *chimera, List_T gregions, bool lowidentityp, Sequence_T queryseq, Sequence_T queryuc,
	      Sequence_T usersegment, Oligoindex_T *oligoindices_major, int noligoindices_major,
	      Oligoindex_T *oligoindices_minor, int noligoindices_minor,
	      Matchpool_T matchpool, Pairpool_T pairpool,
	      Diagpool_T diagpool, Dynprog_T dynprogL, Dynprog_T dynprogM, Dynprog_T dynprogR,
	      Stopwatch_T worker_stopwatch) {
  List_T stage3list;
  Stage3_T nonchimericbest;
  bool testchimerap = false;
  int effective_start, effective_end;


  *mergedp = false;
  *chimera = NULL;

  debug(printf("Calling stage3_from_gregions\n"));
  stage3list = stage3_from_gregions((List_T) NULL,gregions,lowidentityp,queryseq,queryuc,
				    usersegment,oligoindices_major,noligoindices_major,
				    oligoindices_minor,noligoindices_minor,pairpool,diagpool,
				    dynprogL,dynprogM,dynprogR,worker_stopwatch);

  Stage3_recompute_goodness(stage3list);
  stage3list = stage3list_sort(stage3list);

  debug2(printf("Initial search gives stage3list of length %d\n",List_length(stage3list)));

  if (diag_debug == true) {
    return stage3list;
  }

  if (stage3list != NULL) {
    nonchimericbest = (Stage3_T) List_head(stage3list);

    if (chimera_margin <= 0) {
      debug2(printf("turned off\n"));
      testchimerap = false;

    } else if (Stage3_domain(nonchimericbest) < chimera_margin) {
      debug2(printf("Existing alignment is too short, so won't look for chimera\n"));
      testchimerap = false;

#if 0
    } else if (Stage3_fracidentity(nonchimericbest) < CHIMERA_IDENTITY &&
	       Chimera_alignment_break(&effective_start,&effective_end,nonchimericbest,Sequence_ntlength(queryseq),CHIMERA_FVALUE) >= chimera_margin
	       ) {
      debug2(printf("Break in alignment quality at %d..%d detected, so will look for chimera\n",
		    effective_start,effective_end));
      testchimerap = true;
#endif

    } else if (Stage3_largemargin(&effective_start,&effective_end,nonchimericbest,Sequence_ntlength(queryseq)) >= chimera_margin) {
      debug2(printf("Large margin at %d..%d detected, so will look for chimera\n",
		    effective_start,effective_end));
      testchimerap = true;

    } else {
      debug2(printf("Good alignment already with identity %f, so won't look for chimera\n",
		    Stage3_fracidentity(nonchimericbest)));
      testchimerap = false;
    }

    if (testchimerap == true) {
      debug2(printf("Checking for chimera, starting with list length %d\n",List_length(stage3list)));
      stage3list = check_for_chimera(&(*mergedp),&(*chimera),stage3list,effective_start,effective_end,
				     queryseq,queryuc,usersegment,
				     oligoindices_major,noligoindices_major,oligoindices_minor,noligoindices_minor,
				     matchpool,pairpool,diagpool,dynprogL,dynprogM,dynprogR);
    }
  }

  debug2(printf("apply_stage3 returning list of length %d\n",List_length(stage3list)));
  return stage3list;
}
