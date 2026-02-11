save_ex_mask_types(char *hdr, long unsigned int *len, gf_io_t pc)
{
    char *s = NULL;

    if(!struncmp(hdr, "content-type:", 13))
      s = "Content-Type: Text/Plain; charset=US-ASCII\015\012X-";
    else if(!struncmp(hdr, "content-description:", 20))
      s = "Content-Description: Deleted Attachment\015\012X-";
    else if(!struncmp(hdr, "content-transfer-encoding:", 26)
	    || !struncmp(hdr, "content-disposition:", 20))
      s = "X-";

    return((*len = s ? strlen(s) : 0) ? gf_puts(s, pc) : 1);
}
