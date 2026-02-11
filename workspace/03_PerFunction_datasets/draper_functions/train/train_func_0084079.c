MainLibListDel (MainLib ml, MainLibEntry mle)
#else
static void MainLibListDel(ml, mle)
     MainLib ml;
     MainLibEntry mle;
#endif
{
  MainLibEntry cur;


  if( ml->head ){
    if( ml->head == mle ){
      ml->head = mle->next;
    }
    else{
      for(cur=ml->head; cur!=NULL; cur=cur->next){
	if( cur->next == mle ){
	  cur->next = mle->next;
	  break;
	}
      }
    }
  }
}
