blob_put(Tcl_Interp *interp, Ns_DbHandle *handle, char* blob_id,
			char* value)
{
    NsPgConn	*nspgConn = (NsPgConn *) handle->connection;
	int			i, j, segment, value_len, segment_len;
	char		out_buf[8001], query[10000];
	char		*segment_pos, *value_ptr;

    value_len = strlen(value);
    value_ptr = value;

	strcpy(query, "INSERT INTO LOB_DATA VALUES(");
	strcat(query, blob_id);
	strcat(query, ",");
	segment_pos = query + strlen(query);
	segment = 1;

	while (value_len > 0) {
	    segment_len = value_len > 6000 ? 6000 : value_len;
        value_len -= segment_len;
		for (i = 0, j = 0; i < segment_len; i += 3, j+=4) {
		  encode3((unsigned char *)&value_ptr[i], &out_buf[j]);
		}
		out_buf[j] = '\0';
		sprintf(segment_pos, "%d, %d, '%s')", segment, segment_len, out_buf);

		if (Ns_PgExec(handle, query) != NS_DML) {
		  Tcl_DString errString;
		  Tcl_DStringInit(&errString);

		  Tcl_DStringAppend
		    (&errString, "Error inserting data into BLOB\n", -1);

		  if(handle->verbose)
		    {
		      append_PQresultStatus(&errString, nspgConn->res);

		      Tcl_DStringAppend(&errString, "SQL:  ", -1);
		      Tcl_DStringAppend(&errString, query, -1);
		    }

		  Tcl_AppendResult(interp, Tcl_DStringValue(&errString), NULL);

		  Tcl_DStringFree(&errString);

		  return TCL_ERROR;
		}
        value_ptr += segment_len;
		segment++;
	}
    Ns_Log(Notice, "done");
	return TCL_OK;
}
