pcpt_del(pcpt *s) {

	if (s != NULL) {
		int e;

		if (s->luo != NULL) {
			s->luo->del(s->luo);
			s->luo2->del(s->luo2);
			s->icco->del(s->icco);
			s->fp->del(s->fp);
		}
		if (s->mlu != NULL) {
			s->mlu->del(s->mlu);
		}
		if (s->clu != NULL) {
			s->clu->del(s->clu);
		}
		for (e = 0; e < (s->di-3); e++) {
			if (s->nlin[e] != NULL)
				s->nlin[e]->del(s->nlin[e]);
		}

		free(s);
	}
}
