copy_DHParameter(const DHParameter *from, DHParameter *to)
{
memset(to, 0, sizeof(*to));
if(der_copy_heim_integer(&(from)->prime, &(to)->prime)) goto fail;
if(der_copy_heim_integer(&(from)->base, &(to)->base)) goto fail;
if((from)->privateValueLength) {
(to)->privateValueLength = malloc(sizeof(*(to)->privateValueLength));
if((to)->privateValueLength == NULL) goto fail;
if(der_copy_heim_integer((from)->privateValueLength, (to)->privateValueLength)) goto fail;
}else
(to)->privateValueLength = NULL;
return 0;
fail:
free_DHParameter(to);
return ENOMEM;
}
