copy_RSAPrivateKey(const RSAPrivateKey *from, RSAPrivateKey *to)
{
memset(to, 0, sizeof(*to));
*(&(to)->version) = *(&(from)->version);
if(der_copy_heim_integer(&(from)->modulus, &(to)->modulus)) goto fail;
if(der_copy_heim_integer(&(from)->publicExponent, &(to)->publicExponent)) goto fail;
if(der_copy_heim_integer(&(from)->privateExponent, &(to)->privateExponent)) goto fail;
if(der_copy_heim_integer(&(from)->prime1, &(to)->prime1)) goto fail;
if(der_copy_heim_integer(&(from)->prime2, &(to)->prime2)) goto fail;
if(der_copy_heim_integer(&(from)->exponent1, &(to)->exponent1)) goto fail;
if(der_copy_heim_integer(&(from)->exponent2, &(to)->exponent2)) goto fail;
if(der_copy_heim_integer(&(from)->coefficient, &(to)->coefficient)) goto fail;
return 0;
fail:
free_RSAPrivateKey(to);
return ENOMEM;
}
