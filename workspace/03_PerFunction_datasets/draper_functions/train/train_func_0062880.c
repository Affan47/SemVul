rfc2231_free_parmlist(PARMLIST_S **p)
{
    if(*p){
	if((*p)->value)
	  fs_give((void **) &(*p)->value);

	mail_free_body_parameter(&(*p)->seen);
	fs_give((void **) p);
    }
}
