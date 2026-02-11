ecpg_prepared(const char *name, struct connection * con)
{
	struct prepared_statement *this;

	this = ecpg_find_prepared_statement(name, con, NULL);
	return this ? this->stmt->command : NULL;
}
