s48_copy_latin_1_to_string_n(char *string_775X, long len_776X, long vm_string_777X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long shifted_783X;
  long j_782X;
  long bits_781X;
  long c_780X;
  long i_779X;
  long max_778X;
 {  if ((3 == (3 & vm_string_777X))) {
    if ((16 == (31 & ((((*((long *) ((((char *) (-3 + vm_string_777X))) + -8))))>>2))))) {
      goto L27513;}
    else {s48_argument_type_violation(vm_string_777X);
      goto L27513;}}
  else {s48_argument_type_violation(vm_string_777X);
    goto L27513;}}
 L27513: {
  max_778X = ((long)(((unsigned long)(*((long *) ((((char *) (-3 + vm_string_777X))) + -8))))>>8)) / 4;
  if ((len_776X < 0)) {
    goto L27537;}
  else {
    if ((max_778X < len_776X)) {
      goto L27537;}
    else {
      goto L27517;}}}
 L27537: {
s48_range_violation((((len_776X)<<2)), 0, (((max_778X)<<2)));
  goto L27517;}
 L27517: {
  arg0K0 = 0;
  goto L27555;}
 L27555: {
  i_779X = arg0K0;
  if ((i_779X < len_776X)) {
    c_780X = ((unsigned char) (*(string_775X + i_779X)));
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = c_780X;
    goto L27566;}
  else {
    return;}}
 L27566: {
  bits_781X = arg0K0;
  j_782X = arg0K1;
  shifted_783X = arg0K2;
  if ((j_782X < 4)) {
    *((unsigned char *) ((((char *) (-3 + vm_string_777X))) + ((((i_779X)<<2)) + j_782X))) = (unsigned char) ((255 & shifted_783X));
    arg0K0 = (8 + bits_781X);
    arg0K1 = (1 + j_782X);
    arg0K2 = ((long)(((unsigned long)shifted_783X)>>8));
    goto L27566;}
  else {
    arg0K0 = (1 + i_779X);
    goto L27555;}}
}
