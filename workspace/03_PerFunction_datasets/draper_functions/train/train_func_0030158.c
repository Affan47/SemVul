mod_list(void)
{

  unsigned int number_of = sizeof(available_modules) / sizeof(Module_Types);
  unsigned int i,j,l;
  unsigned int k,longest;

  for(i=0,longest=0; i<number_of; i++)
    {
      k = (unsigned int)strlen(available_modules[i].names[1]);
      if(k>longest)
	longest = k;
    }

  k=0;
  do
    {

      for(i=0; (i<4) && (k<number_of); i++)
	{
	  cout << available_modules[k].names[1];
	  if(i<3)
	    {
	      l = longest + 2 - (unsigned int)strlen(available_modules[k].names[1]);
	      for(j=0; j<l; j++)
		cout << ' ';
	    }
	  k++;
	}
      cout << '\n';
    } while (k < number_of);

}
