dounicodefind(XChar2b *target)
{


	int ndx, retval=0;
	int targetval=(target->byte1 <<8) | target->byte2;

	for(ndx=lowestkanji;ndx<highestkanji;ndx++){
		if(translations[ndx]==NULL)
			continue;
		if(compareUnicode(translations[ndx],targetval)){
			retval=ndx;
			break;
		}
	}
	if(retval!=0){
		return translations[retval];
	} else {
		return NULL;
	}
}
