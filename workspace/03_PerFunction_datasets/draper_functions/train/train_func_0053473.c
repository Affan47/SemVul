simple_index_line(char *buf, size_t buflen, ICE_S *ice, long int msgno)
{
    char     *p;
    IFIELD_S *ifield, *previfield = NULL;
    IELEM_S  *ielem;

    if(!buf)
      panic("NULL buf in simple_index_line()");

    if(buflen > 0)
      buf[0] = '\0';

    p = buf;

    if(ice){

      for(ifield = ice->ifield; ifield && p-buf < buflen; ifield = ifield->next){


	if(ifield != ice->ifield && !(previfield && previfield->ctype == iText))
	  *p++ = ' ';


	if(ifield->ctype == iMessNo){
	  ielem = ifield->ielem;
	  if(ielem && ielem->datalen >= ifield->width){
	    if(msgno > 0L)
	      snprintf(ielem->data, ielem->datalen+1, "%*.ld", ifield->width, msgno);
	    else
	      snprintf(ielem->data, ielem->datalen+1, "%*.*s", ifield->width, ifield->width, "");
	  }
	}

	for(ielem = ifield->ielem;
	    ielem && ielem->print_format && p-buf < buflen;
	    ielem = ielem->next){
	  char *src;
	  size_t bytes_added;

	  src = ielem->data;
	  bytes_added = utf8_pad_to_width(p, src,
					  buflen-(p-buf) * sizeof(char),
					  ielem->wid, ifield->leftadj);
	  p += bytes_added;
	}

	previfield = ifield;
      }

      if(p-buf < buflen)
        *p = '\0';
    }

    buf[buflen-1] = '\0';

    return(buf);
}
