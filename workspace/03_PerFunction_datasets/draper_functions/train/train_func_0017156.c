s48_copy_latin_1_to_string(char *string_784X, long vm_string_785X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long shifted_792X;
  long j_791X;
  long bits_790X;
  long c_789X;
  long i_788X;
  long i_787X;
  long max_786X;
 {  if ((3 == (3 & vm_string_785X))) {
    if ((16 == (31 & ((((*((long *) ((((char *) (-3 + vm_string_785X))) + -8))))>>2))))) {
      goto L27589;}
    else {s48_argument_type_violation(vm_string_785X);
      goto L27589;}}
  else {s48_argument_type_violation(vm_string_785X);
    goto L27589;}}
 L27589: {
  max_786X = ((long)(((unsigned long)(*((long *) ((((char *) (-3 + vm_string_785X))) + -8))))>>8)) / 4;
  i_787X = strlen((char *) string_784X);
  if ((i_787X < 0)) {
    goto L27615;}
  else {
    if ((max_786X < i_787X)) {
      goto L27615;}
    else {
      goto L27595;}}}
 L27615: {
s48_range_violation((((i_787X)<<2)), 0, (((max_786X)<<2)));
  goto L27595;}
 L27595: {
  arg0K0 = 0;
  goto L27633;}
 L27633: {
  i_788X = arg0K0;
  if ((i_788X < (strlen((char *) string_784X)))) {
    c_789X = ((unsigned char) (*(string_784X + i_788X)));
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = c_789X;
    goto L27644;}
  else {
    return;}}
 L27644: {
  bits_790X = arg0K0;
  j_791X = arg0K1;
  shifted_792X = arg0K2;
  if ((j_791X < 4)) {
    *((unsigned char *) ((((char *) (-3 + vm_string_785X))) + ((((i_788X)<<2)) + j_791X))) = (unsigned char) ((255 & shifted_792X));
    arg0K0 = (8 + bits_790X);
    arg0K1 = (1 + j_791X);
    arg0K2 = ((long)(((unsigned long)shifted_792X)>>8));
    goto L27644;}
  else {
    arg0K0 = (1 + i_788X);
    goto L27633;}}
}
