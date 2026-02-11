blob_dml_file(Tcl_Interp *interp, Ns_DbHandle *handle, char* blob_id,
			char* filename)
{
    NsPgConn	*nspgConn = (NsPgConn *) handle->connection;
	int			fd, i, j, segment, readlen;
	char		in_buf[6000], out_buf[8001], query[10000];
	char		*segment_pos;

	fd = open (filename, O_RDONLY);

	if (fd == -1)
	{
		Ns_Log (Error, " Error opening file %s: %d(%s)",
				filename, errno, strerror(errno));
		Tcl_AppendResult (interp, "can't open file ", filename,
						 " for reading. ", "received error ",
						 strerror(errno), NULL);
	}

	strcpy(query, "INSERT INTO LOB_DATA VALUES(");
	strcat(query, blob_id);
	strcat(query, ",");
	segment_pos = query + strlen(query);
	segment = 1;

	readlen = read (fd, in_buf, 6000);
	while (readlen > 0) {
		for (i = 0, j = 0; i < readlen; i += 3, j+=4) {
		  encode3((unsigned char *)&in_buf[i], &out_buf[j]);
		}
		out_buf[j] = '\0';
		sprintf(segment_pos, "%d, %d, '%s')", segment, readlen, out_buf);
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
		readlen = read(fd, in_buf, 6000);
		segment++;
	}
	close(fd);
	return TCL_OK;
}
