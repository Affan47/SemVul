create_clause_table() {

	if (clause_table != NULL)
		delete clause_table;
	this->unmark();
	clause_table = new clause_table_t(this->count_clauses());
	this->unmark();
	this->clause_table_recurser(clause_table);
	clause_table->dirty = 0;
}
