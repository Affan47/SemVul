match_compare(const Match *p1, const Match *p2)
{
    if (p1->success > p2->success){
	return -1;
    } else
    if (p1->success < p2->success){
	return 1;
    } else {
	if (p1->fail < p2->fail){
	    return -1;
	} else
	if (p1->fail > p2->fail){
	    return 1;
	}
    }


    if (p1->ptr < p2->ptr){
	return -1;
    } else
    if (p1->ptr > p2->ptr){
	return 1;
    }

    return 0;
}
