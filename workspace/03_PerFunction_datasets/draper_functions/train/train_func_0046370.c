forgetScriptsFrom(scno)
Script scno; {
    Script i;
    for (i=scno; i<namesUpto; ++i)
	freeScript(i);
    dropScriptsFrom(scno-1);
    namesUpto = scno;
    if (numScripts>namesUpto)
	numScripts = scno;
}
