copy_ECParameters(const ECParameters *from, ECParameters *to)
{
memset(to, 0, sizeof(*to));
(to)->element = (from)->element;
switch((from)->element) {
case choice_ECParameters_namedCurve:
if(der_copy_oid(&(from)->u.namedCurve, &(to)->u.namedCurve)) goto fail;
break;
}
return 0;
fail:
free_ECParameters(to);
return ENOMEM;
}
