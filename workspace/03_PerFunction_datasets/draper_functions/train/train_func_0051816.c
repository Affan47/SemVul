PythonHint(PyObject * UNUSED(self), PyObject * args)
{
    PyObject *retval = NULL, *gnubgid = NULL, *tmpobj;
    procrecorddata prochint;
    char szNumber[6];
    char *szHintType;
    int nMaxMoves = -1;

    if (!PyArg_ParseTuple(args, "|i", &nMaxMoves))
        return NULL;

    if (nMaxMoves < 0)
        nMaxMoves = MAX_MOVES;

    if ((ms.gs != GAME_PLAYING)) {
        PyErr_SetString(PyExc_StandardError, _("You must set up a board first."));
    } else

    if (!ms.anDice[0] && !ms.fDoubled && !ms.fResigned) {
        PyErr_SetString(PyExc_StandardError, _("Hints for cube actions not yet implemented"));

    } else

    if (ms.fResigned) {
        PyErr_SetString(PyExc_StandardError, _("Hints for resignations not yet implemented"));

    } else

    if (ms.fDoubled) {
        PyErr_SetString(PyExc_StandardError, _("Hints for take actions not yet implemented"));

    } else if (ms.anDice[0]){
        sprintf (szNumber, "%d", nMaxMoves) ;
        memset(&prochint, 0, sizeof(prochint));
        prochint.pvUserData = PyList_New(0);
        prochint.pfProcessRecord = PythonHint_Callback;
        prochint.avInputData[PROCREC_HINT_ARGIN_SHOWPROGRESS] = (void *)(long)0;
        prochint.avInputData[PROCREC_HINT_ARGIN_MAXMOVES] = (void *)(long)nMaxMoves;
        hint_move (szNumber, FALSE, (void *)&prochint);

        szHintType = "chequer";
        retval = prochint.pvUserData;
    }
    if (retval){
        tmpobj = Py_BuildValue("()");
        gnubgid = PythonGnubgID(NULL, tmpobj);
        Py_DECREF(tmpobj);
        tmpobj = Py_BuildValue("{s:s,s:N,s:N}", "hinttype", szHintType, "gnubgid", gnubgid, "hint", retval);

        retval = tmpobj;
    }

    return retval;
}
