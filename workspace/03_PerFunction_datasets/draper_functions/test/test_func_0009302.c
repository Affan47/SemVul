copy_PKAuthenticator_Win2k(const PKAuthenticator_Win2k *from, PKAuthenticator_Win2k *to)
{
memset(to, 0, sizeof(*to));
if(copy_PrincipalName(&(from)->kdcName, &(to)->kdcName)) goto fail;
if(copy_Realm(&(from)->kdcRealm, &(to)->kdcRealm)) goto fail;
*(&(to)->cusec) = *(&(from)->cusec);
if(copy_KerberosTime(&(from)->ctime, &(to)->ctime)) goto fail;
*(&(to)->nonce) = *(&(from)->nonce);
return 0;
fail:
free_PKAuthenticator_Win2k(to);
return ENOMEM;
}
