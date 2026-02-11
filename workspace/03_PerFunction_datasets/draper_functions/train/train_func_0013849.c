ecpg_prepared(const char *name, struct connection * con, int lineno)
{
	struct prepared_statement *this;

	this = find_prepared_statement(name, con, NULL);
	return this ? this->stmt->command : NULL;
}
