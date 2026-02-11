autovacuum_do_vac_analyze(autovac_table *tab,
						  BufferAccessStrategy bstrategy)
{
	VacuumStmt	vacstmt;


	MemSet(&vacstmt, 0, sizeof(vacstmt));

	vacstmt.type = T_VacuumStmt;
	vacstmt.vacuum = tab->at_dovacuum;
	vacstmt.full = false;
	vacstmt.analyze = tab->at_doanalyze;
	vacstmt.freeze_min_age = tab->at_freeze_min_age;
	vacstmt.freeze_table_age = tab->at_freeze_table_age;
	vacstmt.verbose = false;
	vacstmt.relation = NULL;
	vacstmt.va_cols = NIL;


	autovac_report_activity(tab);

	vacuum(&vacstmt, tab->at_relid, false, bstrategy, tab->at_wraparound, true);
}
