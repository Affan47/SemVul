Sprint(void *ukey, void *udata,btw_t which,void*info)
{
    register SkeyType *key=(SkeyType*)ukey;
    register SdataType *data=(SdataType*)udata;
    static SkeyType *lastkey=NULL;

    if (which == bt_first) {
	ZERO(tin);
	ZERO(tout);
	tcnt=0;
	ZERO(gin);
	ZERO(gout);
	gcnt=0;
	return 0;
    }
    if (which == bt_last || lastkey != NULL && memcmp(lastkey->src,key->src,ADDRLEN(key->src))!=0) {
	if (verbose)
	    printf("ST:%s:%s:%s:%d\n",address(lastkey->src),lltos(tout),lltos(tin),tcnt);
	ADD(gin,gin,tin);
	ADD(gout,gout,tout);
	gcnt+=tcnt;
	ZERO(tin);
	ZERO(tout);
	tcnt=0;
    }
    if (which == bt_last) {
	printf("SG:%s:%s:%d\n", lltos(gout), lltos(gin),gcnt);
	return 0;
    }

    if (verbose > 1) {
	printf("SD:%s:%s:%s:%s:%d\n",address(key->src),key->user,
		lltos(data->sent),lltos(data->recvd),data->count);
    }
    ADD(tin,tin,data->recvd);
    ADD(tout,tout,data->sent);
    tcnt+=data->count;
    lastkey=key;
    return 0;
}
