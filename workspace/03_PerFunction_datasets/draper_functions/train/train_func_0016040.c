valid_table(CTABLE *_object)
{
	return !THIS->conn || !THIS->conn->db.handle;
}
