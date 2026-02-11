s48_register_gc_rootB(char * loc_addr_608X)
{
  char * x_610X;
  char * frame_609X;
 {  frame_609X = (char *)malloc(24);
  if ((frame_609X == NULL)) {
    ps_error("out of memory registering a global root", 0);
    goto L5307;}
  else {
    goto L5307;}}
 L5307: {
  *((long *) frame_609X) = (long) ((((long) (Spermanent_external_rootsS))));
  *((long *) (frame_609X + 8)) = (long) ((((long) NULL)));
  x_610X = Spermanent_external_rootsS;
  if ((x_610X == NULL)) {
    goto L5327;}
  else {
    *((long *) ((Spermanent_external_rootsS) + 8)) = (long) ((((long) frame_609X)));
    goto L5327;}}
 L5327: {
  *((long *) (frame_609X + 16)) = (long) ((((long) loc_addr_608X)));
  Spermanent_external_rootsS = frame_609X;
  return frame_609X;}
}
