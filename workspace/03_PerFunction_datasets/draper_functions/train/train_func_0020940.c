ldapqry_print(LdapQuery *qry, FILE *stream) {
	cm_return_if_fail( qry != NULL );

	ldapsvr_print_data(qry->server, stream);
	ldapctl_print(qry->control, stream);
	fprintf(stream, "entriesRead: %d\n", qry->entriesRead);
	fprintf(stream, "elapsedTime: %d\n", qry->elapsedTime);
	fprintf(stream, "stopFlag: %d\n", qry->stopFlag);
	fprintf(stream, "busyFlag: %d\n", qry->busyFlag);
	fprintf(stream, "agedFlag: %d\n", qry->agedFlag);
	fprintf(stream, "completed: %d\n", qry->completed);
	fprintf(stream, "startTime: %d\n", (int) qry->startTime);
	fprintf(stream, "touchTime: %d\n", (int) qry->touchTime);
	fprintf(stream, "data: %s\n", qry->data?(gchar *)qry->data:"null");
}
