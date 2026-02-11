free_tct_insides(struct tcterm_t *tctp)
{
 if (tctp->tnam != NULL) __my_free(tctp->tnam, strlen(tctp->tnam) + 1);
 if (tctp->cndnam != NULL) __my_free(tctp->cndnam, strlen(tctp->cndnam) + 1);
}
