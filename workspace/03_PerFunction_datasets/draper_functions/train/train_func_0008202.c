cancel_1mipdev(struct tev_t *tevp)
{
 tevp->te_cancel = TRUE;
 __inertial_cancels++;

 if (tevp->tu.tenp == NULL) __misc_terr(__FILE__, __LINE__);

 __my_free((char *) tevp->tu.tenp, sizeof(struct tenp_t));
 tevp->tu.tenp = NULL;
}
