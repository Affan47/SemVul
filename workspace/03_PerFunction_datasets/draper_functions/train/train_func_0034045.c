Curl_smtp_escape_eob(struct connectdata *conn, const ssize_t nread)
{


  ssize_t i;
  ssize_t si;
  struct SessionHandle *data = conn->data;
  struct SMTP *smtp = data->req.protop;
  char *scratch = data->state.scratch;
  char *oldscratch = NULL;


  if(!scratch || data->set.crlf) {
    oldscratch = scratch;

    scratch = malloc(2 * BUFSIZE);
    if(!scratch) {
      failf(data, "Failed to alloc scratch buffer!");

      return CURLE_OUT_OF_MEMORY;
    }
  }


  for(i = 0, si = 0; i < nread; i++) {
    if(SMTP_EOB[smtp->eob] == data->req.upload_fromhere[i]) {
      smtp->eob++;


      if(2 == smtp->eob || SMTP_EOB_LEN == smtp->eob)
        smtp->trailing_crlf = TRUE;
      else
        smtp->trailing_crlf = FALSE;
    }
    else if(smtp->eob) {

      memcpy(&scratch[si], SMTP_EOB, smtp->eob);
      si += smtp->eob;


      if(SMTP_EOB[0] == data->req.upload_fromhere[i])
        smtp->eob = 1;
      else
        smtp->eob = 0;


      smtp->trailing_crlf = FALSE;
    }


    if(SMTP_EOB_FIND_LEN == smtp->eob) {

      memcpy(&scratch[si], SMTP_EOB_REPL, SMTP_EOB_REPL_LEN);
      si += SMTP_EOB_REPL_LEN;
      smtp->eob = 0;
    }
    else if(!smtp->eob)
      scratch[si++] = data->req.upload_fromhere[i];
  }

  if(smtp->eob) {

    memcpy(&scratch[si], SMTP_EOB, smtp->eob);
    si += smtp->eob;
    smtp->eob = 0;
  }


  if(si != nread) {

    data->req.upload_fromhere = scratch;


    data->state.scratch = scratch;


    Curl_safefree(oldscratch);


    data->req.upload_present = si;
  }
  else
    Curl_safefree(scratch);

  return CURLE_OK;
}
