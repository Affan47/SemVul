setImWin(u32 id, Rectangle &rect)
{
	if (id >= NR_IM_WINS) return;

	if (!rect.w || !rect.h || rect.x >= sw || rect.y >= sh)
		memset(&rect, 0, sizeof(rect));

	if (rect.x + rect.w >= sw) rect.w = sw - rect.x;
	if (rect.y + rect.h >= sh) rect.h = sh - rect.y;

	bool active = (FbShellManager::instance()->activeShell() == mShell);

	if (active && intersectRectangles(mWins[id], rect) != Inside) {
		Rectangle oldrect = mWins[id];

		memset(&mWins[id], 0, sizeof(rect));
		mValidWinNum--;

		u32 endx = oldrect.x + oldrect.w, endy = oldrect.y + oldrect.h;
		u16 col = oldrect.x / FW(1);
		u16 row = oldrect.y / FH(1);
		u16 endcol = endx / FW(1);
		u16 endrow = endy / FH(1);

		mShell->expose(col, row, endcol - col + 1, endrow - row + 1);
	}

	if (!mWins[id].w && rect.w) mValidWinNum++;
	mWins[id] = rect;

	if (active) {
		Screen::instance()->enableScroll(!mValidWinNum);
	}

	for (MsgList::iterator it = mWinMsgs[id].begin(); it != mWinMsgs[id].end(); it++) {
		delete[] (s8 *)(*it);
	}

	mWinMsgs[id].clear();
}
