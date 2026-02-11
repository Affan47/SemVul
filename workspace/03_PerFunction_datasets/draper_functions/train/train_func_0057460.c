EndApp()
{
  for (int i=counter-1; i>=0; i--)
  {
	 GivModule* curr = All[SortedAll[i]] ;
#ifdef GIVARO_DEBUG
	 if (curr->name !=0) std::cout << curr->name << " freeing..."  ;
#endif
	 if (curr->f_end !=0) curr->f_end() ;
#ifdef GIVARO_DEBUG
	 if (curr->name !=0) std::cout << "done !" << std::endl ;
#endif
  }
}
