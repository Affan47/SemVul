text2qos(const char *text,struct atm_qos *qos,int flags)
{
    int traffic_class,aal;

    traffic_class = ATM_NONE;
    aal = ATM_NO_AAL;
    do {
	static const unsigned char aal_number[] = { ATM_AAL0, ATM_AAL5 };
	int item;

	item = fetch(&text,"!none","ubr","cbr","vbr","abr","aal0","aal5",NULL);
	switch (item) {
	    case 1:
	    case 2:

	    case 4:
		traffic_class = item;
		break;
	    case 5:
	    case 6:
		aal = aal_number[item-5];
		break;
	    default:
		return -1;
	}
    }
    while (*text == ',' ? text++ : 0);
    if (!traffic_class) return -1;
    if (qos && !(flags & T2Q_DEFAULTS)) memset(qos,0,sizeof(*qos));
    if (qos) qos->txtp.traffic_class = qos->rxtp.traffic_class = traffic_class;
    if (qos && aal) qos->aal = aal;
    if (!*text) return 0;
    if (params(&text,qos ? &qos->txtp : NULL,qos ? &qos->rxtp : NULL))
	return -1;
    if (!*text) return 0;
    switch (fetch(&text,"tx","rx",NULL)) {
	case 0:
	    if (!fetch(&text,":none",NULL)) {
		if (qos) qos->txtp.traffic_class = ATM_NONE;
		if (*text == ',') text++;
		break;
	    }
	    if (params(&text,qos ? &qos->txtp : NULL,NULL)) return -1;
	    break;
	case 1:
	    text -= 2;
	    break;
	default:
	    return -1;
    }
    if (!*text) return 0;
    if (fetch(&text,"rx",NULL)) return -1;
    if (!fetch(&text,":none",NULL) && qos) qos->rxtp.traffic_class = ATM_NONE;
    else if (params(&text,qos ? &qos->rxtp : NULL,NULL)) return -1;
    return *text ? -1 : 0;
}
