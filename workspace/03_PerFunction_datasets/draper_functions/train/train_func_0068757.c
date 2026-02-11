audit_to_inode(struct audit_krule *krule,
				 struct audit_field *f)
{
	if (krule->listnr != AUDIT_FILTER_EXIT ||
	    krule->inode_f || krule->watch || krule->tree ||
	    (f->op != Audit_equal && f->op != Audit_not_equal))
		return -EINVAL;

	krule->inode_f = f;
	return 0;
}
