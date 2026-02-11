print_score(s_player *p1,s_player *p2,s_game *mod)
{
  if(mod->log)
    {
      struct s_score buffer;
      buffer.scoreP1=p1->score;
      buffer.scoreP2=p2->score;
      FILE* save;
      save=fopen("score.sav","a");
      fwrite(&buffer,sizeof(s_score),1,save);
      fclose(save);
    }
  printf("\n FIN DE LA PARTIE \n");
  if((p1->score)==(p2->score))
    printf("\n EGALITE \n");
  else
    if((p1->score)<(p2->score))
      printf("\n VICTOIRE DE %c%c%c \n",p2->name[0],p2->name[1],p2->name[2]);
    else
      printf("\n VICTOIRE DE %c%c%c \n",p1->name[0],p1->name[1],p1->name[2]);
  return;
}
