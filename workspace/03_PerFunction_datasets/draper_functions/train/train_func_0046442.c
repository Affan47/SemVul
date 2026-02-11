gen_load_fortran(
    void *rec_start
    )
{
    char stmnt[FORT_MAX_STMNT];
    struct vars *v = &vars[varnum];

    if (!v->has_data)
	return;

    if (v->ndims == 0 || v->dims[0] != rec_dim) {
	sprintf(stmnt, "* store %s", v->name);
	fline(stmnt);
    }


    if (v->type != NC_CHAR) {
	f_var_init(varnum, rec_start);
    } else {
	v->data_stmnt = fstrstr(rec_start, valnum);
    }

    if (v->ndims >0 && v->dims[0] == rec_dim) {
	return;
    }
    if (v->type != NC_CHAR) {
	sprintf(stmnt, "iret = nf_put_var_%s(ncid, %s_id, %s)",
		nfftype(v->type), v->lname, v->lname);
    } else {
	char *char_expr = fstrstr(rec_start, valnum);
	if(strlen("iret = nf_put_var_(ncid, _id, )") +
	   strlen(nfftype(v->type)) +
	   strlen(v->lname) +
	   strlen(char_expr) > FORT_MAX_STMNT) {
	    derror("FORTRAN statement to assign values to %s too long!",
		   v->lname);
	    exit(9);
	}
	sprintf(stmnt, "iret = nf_put_var_%s(ncid, %s_id, %s)",
		nfftype(v->type), v->lname, char_expr);
	free(char_expr);
    }

    fline(stmnt);
    fline("call check_err(iret)");
}
