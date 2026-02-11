check_disk_stats(int conn, int warn, int crit, char *diskname) {
	char *p;
	int rc=0, value=-1;
	struct xmltree *response;
	struct xmliterator *iter;
	int founddisk=0;

	sendreq(conn, "<d>-1</d>");
	response=xmlparsefd(conn);

	for (iter=xmliteratorinit(response); iter; iter=xmliteratornext(iter)) {
		if (!strcmp(iter->keyword, "isr/DISKS/d/n"))
			founddisk=!strcmp(iter->value, diskname);

		if (!strcmp(iter->keyword, "isr/DISKS/d/p") && founddisk) {
			value=atoi(iter->value);
			break;
		}
	}

	if (value==-1) { rc=3; }
	else if	(crit>0 && value>crit) { rc=2; }
	else if	(crit<0 && value<-crit) { rc=2; }
	else if	(warn>0 && value>warn) { rc=1; }
	else if	(warn<0 && value<-warn) { rc=1; }
	addcheckresult(rc, 'd', diskname, value, warn, crit, 0, 100);
	xmlfreetree(response);
}
