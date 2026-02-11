_dxflookkeyword(int id)
{
    struct keywords *kp = keywords;


    while(kp->id != KW_NULL) {
	if (id == kp->id)
	    return kp->word;

	kp++;
    }


    return NULL;
}
