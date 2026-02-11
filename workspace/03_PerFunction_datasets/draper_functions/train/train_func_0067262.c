fetch_body(INDEXDATA_S *idata)
{
    BODY *body;

    if(idata->bogus || idata->no_fetch){
	idata->bogus = 2;
	return(NULL);
    }

    if(pine_mail_fetchstructure(idata->stream, idata->rawno, &body))
      return(body);

    idata->bogus = 1;
    return(NULL);
}
