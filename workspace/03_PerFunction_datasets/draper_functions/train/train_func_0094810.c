add_child_txn(DbTxn *kid)
{
	TAILQ_INSERT_HEAD(&children, kid, child_entry);
	kid->set_parent(this);
}
