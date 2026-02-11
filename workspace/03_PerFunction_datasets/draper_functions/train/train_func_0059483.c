o_on(id, objchn)
unsigned int id;
register struct obj *objchn;
{
	struct obj *temp;

	while(objchn) {
		if(objchn->o_id == id) return(objchn);
		if (Has_contents(objchn) && (temp = o_on(id,objchn->cobj)))
			return temp;
		objchn = objchn->nobj;
	}
	return((struct obj *) 0);
}
