ListHandleScan( List *list, int (*func)(), void *arg )
{
    while(list) {
	if(list->carhandle)
	    (*func)(&list->carhandle, list, arg);
	GeomHandleScan( list->car, func, arg );
	list = list->cdr;
    }
}
