butTbin_insert(But *but, const char *appText)  {
  bool  saveOldCurs;
  Tbin  *tb;

  assert(MAGIC(but));
  tb = but->iPacket;
  assert(MAGIC(tb));
  saveOldCurs = (!loc_eq(tb->locs[tbin_loCur], tb->locs[tbin_hiCur]) ||
		 (tinNum_next(tb->locs[tbin_loCur].tin, tb) !=
		  tb->maxTins));
  if (saveOldCurs)  {
    tb->locs[tbin_mouse] = tb->locs[tbin_loCur];
    tb->locs[tbin_press] = tb->locs[tbin_hiCur];
    tb->locs[tbin_loCur].tin = tinNum_prev(tb->maxTins, tb);
    tb->locs[tbin_loCur].index = tb->tins[tb->locs[tbin_loCur].tin].len;
    tb->locs[tbin_hiCur] = tb->locs[tbin_loCur];
  }
  insert(but->win->env, appText, tb,
	 but->w - (tb->lMargin + tb->rMargin), NULL);
  checkOffWin(but, 0, TRUE);
  if (saveOldCurs && !loc_eq(tb->locs[tbin_mouse], tb->locs[tbin_press]))  {
    tb->locs[tbin_loCur] = tb->locs[tbin_mouse];
    tb->locs[tbin_hiCur] = tb->locs[tbin_press];
  }
  but_draw(but);
}
