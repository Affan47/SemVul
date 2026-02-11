read_file_stat_bunch(struct activity *act[], int curr, int ifd, int act_nr,
			  struct file_activity *file_actlst)
{
	int i, j, k, p;
	struct file_activity *fal = file_actlst;

	for (i = 0; i < act_nr; i++, fal++) {

		if (((p = get_activity_position(act, fal->id)) < 0) ||
		    (act[p]->magic != fal->magic)) {


			if (lseek(ifd, fal->size * fal->nr * fal->nr2, SEEK_CUR) < (fal->size * fal->nr * fal->nr2)) {
				close(ifd);
				perror("lseek");
				exit(2);
			}
		}
		else if ((act[p]->nr > 0) &&
			 ((act[p]->nr > 1) || (act[p]->nr2 > 1)) &&
			 (act[p]->msize > act[p]->fsize)) {
			for (j = 0; j < act[p]->nr; j++) {
				for (k = 0; k < act[p]->nr2; k++) {
					sa_fread(ifd,
						 (char *) act[p]->buf[curr] + (j * act[p]->nr2 + k) * act[p]->msize,
						 act[p]->fsize, HARD_SIZE);
				}
			}
		}
		else if (act[p]->nr > 0) {
			sa_fread(ifd, act[p]->buf[curr], act[p]->fsize * act[p]->nr * act[p]->nr2, HARD_SIZE);
		}
		else {
			PANIC(act[p]->nr);
		}
	}
}
