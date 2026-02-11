deviceClassUnconfig(device_ *r)
{
	devicePrivate_ *p;
	ReturnErrIf(r == NULL);
	p = r->private;
	ReturnErrIf(p == NULL);

	Debug("Unconfiging %s %s %p", r->class->type, r->refdes, r);

	if(p->rowRName != NULL) {
		free(p->rowRName);
	}

	if(p->rowSName != NULL) {
		free(p->rowSName);
	}

	if(p->historyInterp != NULL) {
		if(historyInterpDestroy(&p->historyInterp)) {
			Warn("Error destroying history interpolation");
		}
	}

	if(p->checkbreakS != NULL) {
		if(checkbreakDestroy(&p->checkbreakS)) {
			Warn("Error destroying break check");
		}
	}

	if(p->checkbreakR != NULL) {
		if(checkbreakDestroy(&p->checkbreakR)) {
			Warn("Error destroying break check");
		}
	}

	return 0;
}
