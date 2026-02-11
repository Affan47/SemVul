Remove(char *name)
{

  MySection  *tmp;

  MySectionListIter li(_list);
  while(li){
    tmp = li.current();
    if(strcmp(tmp->Name(),name)==0){


      _list.remove(tmp);

      delete tmp;

      _number--;
      return;
    }
    li++;
  }
}
