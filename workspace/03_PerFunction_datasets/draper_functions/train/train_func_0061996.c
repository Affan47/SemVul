CommandAnalyseMatch(char *UNUSED(sz))
{
    listOLD *pl;
    moverecord *pmr;
    int nMoves;
    int fStore_crawford;

    if (!CheckGameExists())
        return;

    if (CheckSettings())
        return;

    fStore_crawford = ms.fCrawford;
    nMoves = NumberMovesMatch(&lMatch);

    ProgressStartValue(_("Analysing match; move:"), nMoves);

    IniStatcontext(&scMatch);

    for (pl = lMatch.plNext; pl != &lMatch; pl = pl->plNext) {

        if (AnalyzeGame(pl->p, FALSE) < 0) {


            IniStatcontext(&scMatch);
            break;
        }
        pmr = (moverecord *) ((listOLD *) pl->p)->plNext->p;
        g_assert(pmr->mt == MOVE_GAMEINFO);
        AddStatcontext(&pmr->g.sc, &scMatch);
    }

    multi_debug("wait for all task: analysis");
    MT_WaitForTasks(UpdateProgressBar, 250, fAutoSaveAnalysis);

    ProgressEnd();

#if USE_GTK
    if (fX)
        ChangeGame(NULL);
#endif
    ms.fCrawford = fStore_crawford;

    playSound(SOUND_ANALYSIS_FINISHED);
}
