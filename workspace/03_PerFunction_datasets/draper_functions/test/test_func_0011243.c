writeModelInfo(Journal& jr) const
{

	{
		JournalRecordPair rp(journal);
		rp << "Information on variables" << endrec;
		JournalRecord rec1(journal);
		rec1 << "Number of endogenous:            " << ny() << endrec;
		JournalRecord rec2(journal);
		rec2 << "Number of exogenous:             " << nexog() << endrec;
		JournalRecord rec3(journal);
		rec3 << "Number of static:                " << nstat() << endrec;
		JournalRecord rec4(journal);
		rec4 << "Number of predetermined:         " << npred()+nboth() << endrec;
		JournalRecord rec5(journal);
		rec5 << "Number of forward looking:       " << nforw()+nboth() << endrec;
		JournalRecord rec6(journal);
		rec6 << "Number of both:                  " << nboth() << endrec;
	}


	const ogdyn::PlannerInfo* pinfo = model->get_planner_info();
	if (pinfo) {
		JournalRecordPair rp(journal);
		rp << "Information on planner variables" << endrec;
		JournalRecord rec1(journal);
		rec1 << "Number of Lagrange multipliers:  " << pinfo->num_lagrange_mults << endrec;
		JournalRecord rec2(journal);
		rec2 << "Number of auxiliary variables:   " << pinfo->num_aux_variables << endrec;
		JournalRecord rec3(journal);
		rec3 << "Number of new terms in the tree: " << pinfo->num_new_terms << endrec;
	}


	const ogdyn::ForwSubstInfo* finfo = model->get_forw_subst_info();
	if (finfo) {
		JournalRecordPair rp(journal);
		rp << "Information on forward substitutions" << endrec;
		JournalRecord rec1(journal);
		rec1 << "Number of affected equations:    " << finfo->num_affected_equations << endrec;
		JournalRecord rec2(journal);
		rec2 << "Number of substituted terms:     " << finfo->num_subst_terms << endrec;
		JournalRecord rec3(journal);
		rec3 << "Number of auxiliary variables:   " << finfo->num_aux_variables << endrec;
		JournalRecord rec4(journal);
		rec4 << "Number of new terms in the tree: " << finfo->num_new_terms << endrec;
	}


	const ogp::SubstInfo* sinfo = model->get_subst_info();
	if (sinfo) {
		JournalRecordPair rp(journal);
		rp << "Information on substitutions" << endrec;
		JournalRecord rec1(journal);
		rec1 << "Number of substitutions:         " << sinfo->num_substs << endrec;
	}
}
