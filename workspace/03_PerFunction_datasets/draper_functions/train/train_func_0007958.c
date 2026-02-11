add(FXCommand* command,bool doit,bool merge){
  register FXCommandGroup* g=this;
  register FXuint size=0;


  if(!command){ fxerror("FXCommandGroup::add: NULL command argument.\n"); }


  if(working){ fxerror("FXCommandGroup::add: already working on undo or redo.\n"); }

  working=true;


  cut();


  if(doit) command->redo();


  while(g->group){ g=g->group; }


  if(g->undolist) size=g->undolist->size();


  if(merge && g->undolist && !marked() && command->canMerge() && g->undolist->mergeWith(command)){


    if(this==g){


      space+=g->undolist->size()-size;
      }


    delete command;
    }


  else{


    command->next=g->undolist;
    g->undolist=command;


    if(this==g){


      space+=command->size();


      if(marker!=NOMARK) marker++;
      undocount++;
      }
    }

  FXTRACE((100,"FXUndoList::add: space=%d undocount=%d marker=%d\n",space,undocount,marker));

  working=false;
  }
