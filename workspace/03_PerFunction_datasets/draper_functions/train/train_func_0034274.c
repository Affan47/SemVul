camlidl_apron_scalar_ml2c(value v, struct ap_scalar_t* scalar)
{
value v2 = Field(v,0);
scalar->discr = Tag_val(v);
switch (scalar->discr) {
case 0:
scalar->val.dbl = Double_val(v2);
break;
case 1:
scalar->val.mpq = (mpq_ptr)(Data_custom_val(v2));
break;
case 2:
scalar->val.mpfr = (mpfr_ptr)(Data_custom_val(v2));
break;
default:
caml_failwith("unknown scalar discriminant in camlidl_apron_scalar_ml2c");
}
return;
}
