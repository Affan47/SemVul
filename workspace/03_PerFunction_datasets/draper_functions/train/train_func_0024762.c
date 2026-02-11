DAdestroy(DynArray *da)
{
     int i;

     if (da->destroyfn != NULL)
	  for (i = 0; i< da->maxsize; i++)
	       da->destroyfn(da->objects[i]);

     free(da->objects);
     free(da);
}
