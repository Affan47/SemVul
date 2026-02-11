br_print_mdb_entry(FILE *f, int ifindex, struct rtattr *attr)
{
	struct rtattr *i;
	int rem;
	struct br_mdb_entry *e;

	rem = RTA_PAYLOAD(attr);
	for (i = RTA_DATA(attr); RTA_OK(i, rem); i = RTA_NEXT(i, rem)) {
		e = RTA_DATA(i);
		print_mdb_entry(f, ifindex, e);
	}
}
