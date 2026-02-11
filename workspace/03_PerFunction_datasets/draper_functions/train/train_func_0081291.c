event_true_key(sharps, s, modeindex, modmap, modmul)
int sharps;
char *s;
int modeindex;
char modmap[7];
int modmul[7];

{
  char basemap[7];
  int basemul[7];
  struct key* akey;
  int minor;
  minor =0;
  if (modeindex >0 && modeindex <4) minor = 1;

  setmap(sharps, basemap, basemul);
  altermap(basemap, basemul, modmap, modmul);
  if (xinbody) {
    akey = newkey(s, sharps, basemap, basemul);
    addfeature(KEY, akey);
    set_keysig(cv->keysig, akey);
  };
  if (xinhead) {
    if (thetune.keysig == NULL) {
      thetune.keysig = newkey(s, sharps, basemap, basemul);
    } else {
      event_warning("Key specified twice");
    };
    xinbody = 1;
    xinhead = 0;
    setvoice(1);
    start_body();
  };
}
