get_key(char *getkey)
{
  CURLcode res;
  char errorbuffer[CURL_ERROR_SIZE];
  char request[MAX_URL];
  struct curl_writer_ctx ctx;

  memset(&ctx,0,sizeof(ctx));

  if(strncmp(getkey,"0x",2)==0)
    getkey+=2;

  fprintf(output,"KEY 0x%s BEGIN\n",getkey);

  sprintf(request,"%s://%s%s%s%s",opt->scheme,opt->host,
	  opt->port?":":"",opt->port?opt->port:"",opt->path?opt->path:"/");

  curl_easy_setopt(curl,CURLOPT_URL,request);
  curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,curl_writer);
  ctx.stream=output;
  curl_easy_setopt(curl,CURLOPT_FILE,&ctx);
  curl_easy_setopt(curl,CURLOPT_ERRORBUFFER,errorbuffer);

  res=curl_easy_perform(curl);
  if(res!=CURLE_OK)
    {
      fprintf(console,"gpgkeys: %s fetch error %d: %s\n",opt->scheme,
	      res,errorbuffer);
      fprintf(output,"\nKEY 0x%s FAILED %d\n",getkey,curl_err_to_gpg_err(res));
    }
  else
    {
      curl_writer_finalize(&ctx);
      if(!ctx.flags.done)
	{
	  fprintf(console,"gpgkeys: no key data found for %s\n",request);
	  fprintf(output,"\nKEY 0x%s FAILED %d\n",
		  getkey,KEYSERVER_KEY_NOT_FOUND);
	}
      else
	fprintf(output,"\nKEY 0x%s END\n",getkey);
    }

  return curl_err_to_gpg_err(res);
}
