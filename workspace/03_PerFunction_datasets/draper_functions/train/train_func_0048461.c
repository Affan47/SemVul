copy_Validity(const Validity *from, Validity *to)
{
memset(to, 0, sizeof(*to));
if(copy_Time(&(from)->notBefore, &(to)->notBefore)) goto fail;
if(copy_Time(&(from)->notAfter, &(to)->notAfter)) goto fail;
return 0;
fail:
free_Validity(to);
return ENOMEM;
}
