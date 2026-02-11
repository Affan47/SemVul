dump_list(const struct idlist *idp)
{
	if (!idp) {
		report_build(stdout, GT_(" <empty>"));
	} else while (idp) {
	    char *t = sdump(idp->id, strlen(idp->id));
	    report_build(stdout, " %s = %s%s", t, str_uidmark(idp->val.status.mark), idp->next ? "," : "");
	    free(t);
	    idp = idp->next;
	}
}
