sal_sem_destroy(sal_sem_t b)
{
    sem_ctrl_t *s = (sem_ctrl_t *) b;

    if (s == NULL) {
	return;
    }


    sal_free(s);
}
